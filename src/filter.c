// this example shows how to read
// an nc file holding mt data,
// generate and filter and calculate
// the confolution with that filter
#include <stdio.h>
#include <stdlib.h>
#include "mt/io.h"
#include "mt/periods.h"
#include "mt/filter.h"

#define WAVE 4.
#define NC_OUT "mtout.nc"

int main(int argc, char *argv[]) {
  int period_id, i;
  
  if(argc < 2) {
    printf("nc file not specified\n");
    exit(EXIT_FAILURE);
  }
  period_id = argc < 3 ? 1 : atoi(argv[2]);
  if(period_id < 1) {
    printf("period id is too small\n");
    exit(EXIT_FAILURE);
  } 
  
  struct mt *mt = mt_read_nc(argv[1]);
  struct period *p = mt_periods_gen(300, 12000, 1.1,
				    mt->len, mt->dt, WAVE);
  struct period *it = p;

  for(i = 1; i < period_id; i++) {
    if(it->next == NULL) {
      printf("period id is too large\n");
      exit(EXIT_FAILURE);
    }
    it = it->next;
  }
  //printf("%f\n", it->p);
  struct filter *f = mt_filter_gen(it);
  struct fmt *fmt = mt_filter_conv(mt, f, WAVE);

  //mt_print_fmt(fmt);
  mt_write_nc(fmt, NC_OUT, &it->p);
  
  free(fmt);
  mt_periods_free(p);
  free(mt);
  exit(EXIT_SUCCESS);
}
