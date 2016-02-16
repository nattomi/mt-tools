/* compile me with: -lm */ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <json/json.h>
#include <stdbool.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

const float mu = 4*M_PI*10E-7;

struct layer {
  float sigma;
  float d;
  struct layer *prev;
};

//float complex imped(float, int, struct layer *); 

void cleanup(struct layer *l) {
  struct layer *it;
  while(l) {
    it = l;
    l = l->prev;
    free(it);
  }
}

struct layer *layers2list(char *str) {
  json_object *jobj = json_tokener_parse(str);
  if(json_object_get_type(jobj)!=json_type_array) {
    printf("Input error: first argument is not a JSON array.\n");
    exit(EXIT_FAILURE);
  }
  int nl = json_object_array_length(jobj);
  json_object *jvalue;
  struct layer *last = NULL;
  struct layer *prev = NULL;
  struct layer *ll;
  bool no_sigma, no_d;
  float sigma, d;
  bool cup;
  int i;
  for(i = 0; i < nl; ++i) {
    jvalue = json_object_array_get_idx(jobj, i);
    if(json_object_get_type(jvalue)!=json_type_object) {
      printf("Input error: array entry is not a json object.\n");
      exit(EXIT_FAILURE);
    }
    
    no_sigma = true;
    no_d = true;
    json_object_object_foreach(jvalue, key, val) {
      if(strcmp(key, "sigma") == 0) {
	if(no_sigma) {
	  sigma = json_object_get_double(val);
	  no_sigma = false;
	}
      }
      if(strcmp(key, "d") == 0) {
	if(no_d) {
	  d = json_object_get_double(val);
	  no_d = false;
	}	
      }
    }
    cup = false;
    if(no_sigma) {
      printf("Input error: array entry doesn't contain a 'sigma' property\n");
      cup = true;
    }
    if(no_d && i < nl - 1) {
      printf("Input error: array entry doesn't contain a 'd' property\n");
      cup = true;
    }
    ll = (struct layer *)malloc(sizeof(struct layer));
    if(ll == NULL) {
      cup = true;
    }
    if(cup) {
      cleanup(last);
      exit(EXIT_FAILURE);
    }
    ll->sigma = sigma;
    ll->d = d;
    ll->prev = prev;
    prev = last = ll;
  }
  
  return last;
};

void print_usage(void) {
  printf("Input error: first and second argument must be a json string\n");
}

int main(int argc, char **argv) {
  
  if(argc < 3) {
    print_usage();
    exit(EXIT_FAILURE);
  }
  //json2list(argv[1]);
  
  json_object *jobj = json_tokener_parse(argv[2]);
  if(json_object_get_type(jobj)!=json_type_array) {
    printf("Input error: second argument is not a JSON array.\n");
    printf("%s\n", argv[2]);
    printf("%s\n", argv[3]);
    exit(EXIT_FAILURE);
  }
  
  struct layer *layerlist = layers2list(argv[1]);
  int nf = json_object_array_length(jobj);
  int i;
  json_object *jvalue;
  float omega;
  float complex g, iwm, coth_gd;
  struct layer *l;
  float complex Z;
  printf("freq Zreal Zimag rhoa\n");
  for(i = 0; i < nf; ++i) {
    jvalue = json_object_array_get_idx(jobj, i);
    omega = json_object_get_double(jvalue);
    l = layerlist;
    Z = csqrt(I * omega * mu / l->sigma);
    l = l->prev;
    while(l) {
      g = csqrt(I * omega * mu * l->sigma);
      iwm = I * omega * mu;
      coth_gd = 1 / ctanh(g * l->d);
      Z *= g / iwm;
      Z = (Z * coth_gd + 1) / (Z + coth_gd);
      Z *= iwm / g;
      l = l->prev;
    }
    printf("%f %f %f %f\n", omega, creal(Z), cimag(Z), pow(cabs(Z), 2) / (omega * mu));
  }
  cleanup(layerlist);
  return 0;
} 

