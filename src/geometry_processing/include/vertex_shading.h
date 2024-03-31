#ifndef VERTEX_PROCESSING_H
#define VERTEX_PROCESSING_H

#include "obj/include/objpar.h"

typedef struct OBJECT_DATA_T {
  objpar_data_t interprt;
  void * stream; // This exists bc api's objpar_data_t points at reserved memory
} obj_data;

obj_data init_obj_data(const char * file_name);
void debug_positions(obj_data the_obj_data);
void debug_normals(obj_data the_obj_data);
void debug_texcoords(obj_data the_obj_data);
void debug_faces(obj_data the_obj_data);
void free_obj_data(obj_data the_obj_data);

#define DEBUG_OBJ_DATA(type) void debug_##type##s(obj_data the_obj_data) {     \
  for(unsigned int i = 0; i < the_obj_data.interprt.type##_count               \
                                * the_obj_data.interprt.type##_width;          \
      i += the_obj_data.interprt.type##_width) {                               \
    for(unsigned int j = 0; j < the_obj_data.interprt.type##_width; j++) {     \
      printf("%f ", the_obj_data.interprt.p_##type##s[i + j]);                 \
    }                                                                          \
    printf("\n");                                                              \
  }                                                                            \
}

typedef struct MESH_DATA_T {
  objpar_mesh_t interprt;
  void * stream; // This exists bc api's objpar_mesh_t points at reserved memory
} mesh_data;

mesh_data init_mesh_data(obj_data the_obj_data);
void free_mesh_data(mesh_data the_mesh_data);

#endif
