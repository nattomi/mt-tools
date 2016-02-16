#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "periods.h"

void mt_periods_free(struct period *p) {
  struct period *it;
  while(p) {
    it = p;
    p = p->next;
    free(it);
  }
}

struct period *mt_periods_gen(float plower, float pupper, float rlkoz,
			      int m, float dt, float wave) {
  struct period *first = NULL;
  struct period *prev, *this;
  int i;
  float p;
  int ns;
  int ld = 1;
  int m1 = m;
  int np = floor(log(pupper / plower) / log(rlkoz)) + 2.;

  for(i = 0; i < np; i++) {
    this = (struct period *)malloc(sizeof(struct period));
    if(this == NULL) {
      // FIXME: do some cleanup somehow
      //      mt_periods_free(first);
      printf("Could not allocate memory\n");
      exit(EXIT_FAILURE);
    }

    p = plower * pow(rlkoz, i);
    ns = floor(wave * p / dt);
    while(p / dt >= 25) {
      dt = 2 * dt;
      ns = (int) ns / 2; // FIXME: would floor be more appropriate?
      ld = 2 * ld;
      m1 = (int) (m + 1) / ld; // FIXME: would floor be more appropriate?
    }
    this->p = p;
    this->ns = ns;
    this->dt = dt;
    this->ld = ld;
    this->mt = (int) m1 / floor(p / dt) + 1; // FIXME: would floor be more appropriate?
    this->next = NULL;

    if(i == 0)
      first = prev = this;
    else {
      prev->next = this;
      prev = this;
    }
  }

  return first;
}
