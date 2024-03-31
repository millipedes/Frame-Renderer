#ifndef MMTL_PARSER_H
#define MMTL_PARSER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct REFLECTION_CONSTANT_T {
  double r;
  double g;
  double b;
} reflection_constant;

typedef struct MMTL_ENTRY_T {
  reflection_constant specular;
  reflection_constant diffuse;
  reflection_constant ambient;
} mmtl_entry;

typedef struct MMTL_DATA {
  mmtl_entry * entries;
  size_t qty_entries;
  size_t pow_two_entries;
} mmtl_data;

mmtl_data init_mmtl_data(const char * file_name);
void free_mmtl_data(mmtl_data the_mmtl_data);

#endif
