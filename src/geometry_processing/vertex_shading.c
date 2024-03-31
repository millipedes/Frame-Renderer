#include "include/vertex_shading.h"

obj_data init_obj_data(const char * file_name) {
  obj_data the_obj_data = {};
  size_t file_size = 0;
  void * file_data = open_file(file_name, &file_size);
  the_obj_data.stream = malloc(objpar_get_size(file_data, file_size));
  objpar((const char *)file_data, file_size, the_obj_data.stream,
      &the_obj_data.interprt);
  free(file_data);
  return the_obj_data;
}

// void debug_normals(obj_data the_obj_data) { ... }
DEBUG_OBJ_DATA(normal)
// void debug_positions(obj_data the_obj_data) { ... }
DEBUG_OBJ_DATA(position)
// void debug_texcoords(obj_data the_obj_data) { ... }
DEBUG_OBJ_DATA(texcoord)

void debug_faces(obj_data the_obj_data) {
  for(unsigned int i = 0;
      i < the_obj_data.interprt.face_count * the_obj_data.interprt.face_width * 3;
      i += the_obj_data.interprt.face_width * 3) {
    for(unsigned int j = 0; j < the_obj_data.interprt.face_width; j += 3) {
      printf("%d %d %d",
          the_obj_data.interprt.p_faces[i + j + OBJPAR_V_IDX],
          the_obj_data.interprt.p_faces[i + j + OBJPAR_VN_IDX],
          the_obj_data.interprt.p_faces[i + j + OBJPAR_VT_IDX]);
    }
    printf("\n");
  }
}

void free_obj_data(obj_data the_obj_data) {
  if(the_obj_data.stream)
    free(the_obj_data.stream);
}

mesh_data init_mesh_data(obj_data the_obj_data) {
  mesh_data the_mesh_data = {};
  if(the_obj_data.interprt.face_width != 3) {
    fprintf(stderr,
        "[INIT_MESH_DATA]: Unable to generate mesh (not pre-faced)");
  } else {
    the_mesh_data.stream
      = malloc(objpar_get_mesh_size(&the_obj_data.interprt));
    assert(objpar_build_mesh(&the_obj_data.interprt,
          the_mesh_data.stream, &the_mesh_data.interprt));
  }
  return the_mesh_data;
}

void free_mesh_data(mesh_data the_mesh_data) {
  if(the_mesh_data.stream)
    free(the_mesh_data.stream);
}
