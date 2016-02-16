 #include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <netcdf.h>
#include "io.h"

/* Handle errors by printing an error message and exiting with a          
 * non-zero status. */
#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}

const char *chnames[] = {"ex", "ey", "hx", "hy"};

struct mt *mt_read_nc(char *filename) {
  int ncid, varid;
  size_t l;
  /* Loop indexes, and error handling. */
  int retval;
  int ncol = sizeof(chnames) / sizeof(char*);
  int i;
  struct mt *MT;

  /* Open the file. NC_NOWRITE tells netCDF we want read-only access      
   * to the file.*/
  if((retval = nc_open(filename, NC_NOWRITE, &ncid)))
    ERR(retval);
  if((retval = nc_inq_dimid(ncid, "time", &varid)))
    ERR(retval);
  if((retval = nc_inq_dimlen(ncid, varid, &l)))
    ERR(retval);


  MT = malloc(offsetof(struct mt, data) + l * sizeof MT->data);
  if(MT == NULL) {
    //FIXME: Some error handling comes here
  }
  MT->len = l;
  if((retval = nc_get_att_float(ncid, NC_GLOBAL, "dt", &(MT->dt))))
    ERR(retval);
 
  for(i = 0; i < ncol; i++) {
    /* Get the varid of the data variable, based on its name. */
    if((retval = nc_inq_varid(ncid, chnames[i], &varid)))
      ERR(retval);
    if((retval = nc_get_att_float(ncid, varid, "scale", &(MT->scale[i]))))
      ERR(retval);
    /* Read the data. */
    if((retval = nc_get_var_int(ncid, varid, &(MT->data[i * l]))))
      ERR(retval);
  }

  /* Close the file, freeing all resources. */
  if((retval = nc_close(ncid)))
    ERR(retval); 
  return MT;
}

void mt_write_nc(struct fmt *fmt, char *filename, float *p) {
  int ncid, dimid;
  int varids[2 * NCOL];
  int i, j, retval;
  char varname[] = "xxx";
  float *re, *im;
 
  if((retval = nc_create(filename, NC_CLOBBER, &ncid)))
    ERR(retval);

  if((retval = nc_def_dim(ncid, "time", fmt->len, &dimid)))
    ERR(retval);

  for(i = 0; i < NCOL; i++) {
    varname[0] = chnames[i][0];
    varname[1] = chnames[i][1];

    varname[2] = 'r';
    if((retval = nc_def_var(ncid, varname, NC_FLOAT, 1,
			    &dimid, &varids[2 * i])))
      ERR(retval);

    varname[2] = 'i';
    if((retval = nc_def_var(ncid, varname, NC_FLOAT, 1,
			    &dimid, &varids[2* i + 1])))
      ERR(retval);

  }

  if((retval = nc_put_att_float(ncid, NC_GLOBAL, "period",
				NC_FLOAT, 1, p)))
    ERR(retval);

  /* End define mode. This tells netCDF we are done defining
   * metadata. */
  if((retval = nc_enddef(ncid)))
    ERR(retval);

  re = (float *)malloc(fmt->len * sizeof(float));
  im = (float *)malloc(fmt->len * sizeof(float));
 
  for(i = 0; i < NCOL; i++) {
    for(j = 0; j < fmt->len; j++) {
      re[j] = creal(fmt->data[i * fmt->len + j]);
    }
    if((retval = nc_put_var_float(ncid, varids[2 * i], re)))
      ERR(retval);

    for(j = 0; j < fmt->len; j++) {
      im[j] = cimag(fmt->data[i * fmt->len + j]);
    }
    if((retval = nc_put_var_float(ncid, varids[2 * i + 1], im)))
      ERR(retval);
    
  }
  free(re);
  free(im);

  /* Close the file. This frees up any internal netCDF resources
   * associated with the file, and flushes any buffers. */
  if((retval = nc_close(ncid)))
    ERR(retval);
  
}

void mt_print_mt(struct mt *mt) {
  int i, j;
  for(i = 0; i < mt->len; i++) {
    for(j = 0; j < NCOL; j++)
      printf("%d ", mt->data[j * mt->len  + i]);
    printf("\n");
  }
}

void mt_print_fmt(struct fmt *fmt) {
  int i, j;
  float complex c;

  for(i = 0; i < fmt->len; i++) {
    for(j = 0; j < NCOL; j++) {
      c = fmt->data[j * fmt->len + i];
      printf("%f %f ", creal(c), cimag(c));
    }
    printf("\n");
  }

}
