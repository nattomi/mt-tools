// this example shows how to read
// an nc file holding mt data and
// print it's content to stdout
#include <stdio.h>
#include <stdlib.h>
#include "mt/io.h"

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("nc file not specified\n");
    exit(EXIT_SUCCESS);
  }
  struct mt *mt = mt_read_nc(argv[1]);
  mt_print_mt(mt);
  free(mt);
  exit(EXIT_SUCCESS);
}
