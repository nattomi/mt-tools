#include <complex.h>

struct filter {
  size_t len;
  float dt;
  int ld;
  int mt;
  float complex coeffs[1];
};

struct filter *mt_filter_gen(struct period *p);

struct fmt *mt_filter_conv(struct mt *mt, struct filter *f, float wave);
