#ifndef MMTL_PARSER_H
#define MMTL_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MMTL_LINE_LEN 1024

#define SPACE ' '
#define AMBIENT_STR "Ka"
#define DIFFUSE_STR "Kd"
#define SPECULAR_STR "Ks"

typedef struct REFLECTION_CONSTANT_T {
  double r;
  double g;
  double b;
} reflection_constant;

typedef enum {
  AMBIENT,
  DIFFUSE,
  SPECULAR,
} rc_type;

reflection_constant parse_rc(char * line);

typedef struct MMTL_ENTRY_T {
  reflection_constant ambient;
  reflection_constant diffuse;
  reflection_constant specular;
} mmtl_entry;

void debug_mmtl_entry(mmtl_entry the_mmtl_entry);

#define REALLOC_MMTL_ENTRIES(the_mmtl_data, entry, entry_enum)                                  \
      the_mmtl_data.qty_##entry++; \
      if(!the_mmtl_data.entries) { \
        the_mmtl_data.entries = calloc(1, sizeof(struct MMTL_ENTRY_T)); \
      } else if(is_max_among_entries(the_mmtl_data, entry_enum)) { \
        the_mmtl_data.entries = realloc(the_mmtl_data.entries, \
            the_mmtl_data.qty_ambient * sizeof(struct MMTL_ENTRY_T)); \
      }

typedef struct MMTL_DATA {
  mmtl_entry * entries;
  size_t qty_ambient;
  size_t qty_diffuse;
  size_t qty_specular;
} mmtl_data;

mmtl_data init_mmtl_data(const char * file_name);
mmtl_data add_mmtl_entry(mmtl_data the_mmtl_data, reflection_constant rc,
    rc_type type);
size_t is_max_among_entries(mmtl_data the_mmtl_data, rc_type type);
void debug_mmtl_data(mmtl_data the_mmtl_data);
void free_mmtl_data(mmtl_data the_mmtl_data);

#endif
