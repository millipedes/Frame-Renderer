#include "include/mmtl_parser.h"

mmtl_data init_mmtl_data(const char * file_name) {
  mmtl_data the_mmtl_data = (mmtl_data){};
  FILE * fp = fopen(file_name, "r");
  fclose(fp);
  return the_mmtl_data;
}

void free_mmtl_data(mmtl_data the_mmtl_data) {
  if(the_mmtl_data.entries)
    free(the_mmtl_data.entries);
}
