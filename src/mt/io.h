#include <complex.h>

#define NCOL 4

struct mt {
  size_t len;
  float dt;
  float scale[NCOL];
  int data[NCOL];
};

struct fmt {
  size_t len;
  float complex data[NCOL]; 
};

struct mt *mt_read_nc(char *filename);

void mt_write_nc(struct fmt *fmt, char *filename, float *p);

void mt_print_mt(struct mt *mt);

void mt_print_fmt(struct fmt *fmt);
