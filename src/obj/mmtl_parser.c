#include "include/mmtl_parser.h"

reflection_constant parse_rc(char * line) {
  char * position = strchr(line, SPACE) + 1;
  double r = atof(position);
  position = strchr(position, SPACE) + 1;
  double g = atof(position);
  position = strchr(position, SPACE) + 1;
  double b = atof(position);
  return (reflection_constant){r, g, b};
}

void debug_mmtl_entry(mmtl_entry the_mmtl_entry) {
  printf("Ambient: (%.2f, %.2f, %.2f) ", the_mmtl_entry.ambient.r,
      the_mmtl_entry.ambient.g, the_mmtl_entry.ambient.b);
  printf("Diffuse: (%.2f, %.2f, %.2f) ", the_mmtl_entry.diffuse.r,
      the_mmtl_entry.diffuse.g, the_mmtl_entry.diffuse.b);
  printf("Specular: (%.2f, %.2f, %.2f)\n", the_mmtl_entry.specular.r,
      the_mmtl_entry.specular.g, the_mmtl_entry.specular.b);
}

mmtl_data init_mmtl_data(const char * file_name) {
  mmtl_data the_mmtl_data = (mmtl_data){0};
  char buf[MAX_MMTL_LINE_LEN] = {0};
  FILE * fp = fopen(file_name, "r");

  while(fgets(buf, MAX_MMTL_LINE_LEN, fp)) {
    if(!strncmp(buf, AMBIENT_STR, sizeof(AMBIENT_STR) - 1)) {
      the_mmtl_data = add_mmtl_entry(the_mmtl_data, parse_rc(buf), AMBIENT);
    } else if(!strncmp(buf, DIFFUSE_STR, sizeof(DIFFUSE_STR) - 1)) {
      the_mmtl_data = add_mmtl_entry(the_mmtl_data, parse_rc(buf), DIFFUSE);
    } else if(!strncmp(buf, SPECULAR_STR, sizeof(SPECULAR_STR) - 1)) {
      the_mmtl_data = add_mmtl_entry(the_mmtl_data, parse_rc(buf), SPECULAR);
    }
  }

  debug_mmtl_data(the_mmtl_data);

  fclose(fp);
  return the_mmtl_data;
}

mmtl_data add_mmtl_entry(mmtl_data the_mmtl_data, reflection_constant rc, rc_type type) {
  switch(type) {
    case AMBIENT:
      REALLOC_MMTL_ENTRIES(the_mmtl_data, ambient, AMBIENT)
      the_mmtl_data.entries[the_mmtl_data.qty_ambient - 1].ambient = rc;
      break;
    case DIFFUSE:
      REALLOC_MMTL_ENTRIES(the_mmtl_data, diffuse, DIFFUSE)
      the_mmtl_data.entries[the_mmtl_data.qty_diffuse - 1].diffuse = rc;
      break;
    case SPECULAR:
      REALLOC_MMTL_ENTRIES(the_mmtl_data, specular, SPECULAR)
      the_mmtl_data.entries[the_mmtl_data.qty_specular - 1].specular = rc;
      break;
  }
  return the_mmtl_data;
}

size_t is_max_among_entries(mmtl_data the_mmtl_data, rc_type type) {
  int array[3] = {the_mmtl_data.qty_ambient, the_mmtl_data.qty_diffuse,
    the_mmtl_data.qty_specular};
  int max = array[type];
  for(int i = 1; i < 3; i++)
    if(max <= array[i])
      return 0;
  return 1;
}

void debug_mmtl_data(mmtl_data the_mmtl_data) {
  if(the_mmtl_data.qty_ambient != the_mmtl_data.qty_diffuse
      || the_mmtl_data.qty_ambient != the_mmtl_data.qty_specular
      || the_mmtl_data.qty_diffuse != the_mmtl_data.qty_specular) {
    fprintf(stderr, "[DEBUG_MMTL_DATA]: Unable to accurately debug because:\n\t"
        "ambient == diffuse ? %s\n\tambient == specular ? %s\n\tdiffuse == specular ? %s\n",
        (the_mmtl_data.qty_ambient == the_mmtl_data.qty_diffuse) ? "true" : "false",
        (the_mmtl_data.qty_ambient == the_mmtl_data.qty_specular) ? "true" : "false",
        (the_mmtl_data.qty_diffuse == the_mmtl_data.qty_specular) ? "true" : "false"
        );
    exit(1);
  }
  for(size_t i = 0; i < the_mmtl_data.qty_ambient; i++)
    debug_mmtl_entry(the_mmtl_data.entries[i]);
}

void free_mmtl_data(mmtl_data the_mmtl_data) {
  if(the_mmtl_data.entries)
    free(the_mmtl_data.entries);
}
