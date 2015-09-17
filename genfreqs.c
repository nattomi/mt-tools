#include <stdio.h>
#include <json/json.h>
#include <stdlib.h>

void printUsage(void) {
  printf("genfreqs from to length\n");
}

int main(int argc, char **argv) {
  if(argc < 4) {
    printUsage();
    exit(EXIT_FAILURE);
  }
  float from = atof(argv[1]);
  float to = atof(argv[2]);
  if(to <= from) { 
    printf("argument 'to' must be greater than 'from'\n");
    exit(EXIT_FAILURE);
  }
  int len = atoi(argv[3]);
  float step = (to - from) / len;
  json_object *jarray = json_object_new_array();
  int i;
  float freq = from;
  json_object *jfreq;
  for(i=0;i<len;i++) {
    jfreq = json_object_new_double(freq);
    json_object_array_add(jarray, jfreq);
    freq += step;
  }

  printf("%s",json_object_to_json_string(jarray));
  
  return 0;
} 

