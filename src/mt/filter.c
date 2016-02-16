#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stddef.h>
#include "io.h"
#include "periods.h"
#include "filter.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct filter *mt_filter_gen(struct period *p) {
  float plower = p->p / 1.1;
  float pupper = p->p * 1.1;
  float q = 2. * M_PI * p->dt;
  float r, c1, c2;
  float complex u;
  struct filter *f;
  int i;
  
  f = malloc(offsetof(struct filter, coeffs) + (p->ns + 1) * sizeof f->coeffs);
  if(f == NULL) {
    printf("Could not allocate memory\n");
    exit(EXIT_FAILURE);
  }
  f->len = p->ns;
  f->dt = p->dt;
  f->ld = p->ld;
  f->mt = p->mt;
  f->coeffs[0] = u = p->dt * (2. / plower - 2. / pupper);

  for(i = 1; i < p->ns + 1; i++) {
    r = -(1. + cos(M_PI * i / p->ns)) / 2. / M_PI / i;
    c1 = sin(q / pupper * i) - sin(q / plower * i);
    c1 *= r;
    c2 = cos(q / pupper * i) - cos(q / plower * i);
    c2 *= r;
    f->coeffs[i] = c1 + c2 * I; 
    u += 2. * (fabs(c1) + fabs(c2) * I);
  }
  r = creal(u) / cimag(u);
  for(i = 1; i < p->ns + 1; i++)
    f->coeffs[i] *= r;
  
  return f;
}

struct fmt *mt_filter_conv(struct mt *mt, struct filter *f, float wave) {
  int i, j, i1, k, ind, n; 
  int l, la, lf;
  int m, u;
  struct fmt *fmt;
  float complex c;
  
  fmt = malloc(offsetof(struct fmt, data) + f->mt * sizeof fmt->data);
  if(fmt == NULL) {
    printf("Could not allocate memory\n");
    exit(EXIT_FAILURE);
  }
  fmt->len = f->mt;
  
  k = (int) f->len / floor(wave);
  for(i = 0; i < NCOL; i++) {
    i1 = mt->data[i * mt->len];
    for(j = 0; j < fmt->len; j++) {
      fmt->data[i * fmt->len + j] = 0.;
      l = 1 + (k * j - f->len) * f->ld;
      // la: max(l,1) serial number of the data where the first component
      //     of the filter is stored
      la = l < 1 ? 1 : l;
      // lf: where the last component of the filter is stored
      lf = l + 2 * f->len * f->ld;     
      for(l = la; l < lf + 1; l = l + f->ld) {
      	m = l < mt->len ? l : mt->len;
      	u = mt->data[i * mt->len + m - 1] - i1;
      	ind = (int) (l - 1) / f->ld;
      	ind -= k * j;
      	n = abs(ind);
	c = u * mt->scale[i] * f->coeffs[n];
	u = ind < 0 ? -1 : 1;
      	fmt->data[i * fmt->len + j] += creal(c) + cimag(c) * u * I;	  
      }
    }
  }

  return fmt;
}
