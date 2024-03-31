#include "canvas/include/canvas.h"
#include "obj/include/objpar_wrapper.h"

int main(void) {
  canvas the_canvas = init_canvas(1000, 1000, MIN_COL, MIN_COL, MIN_COL);
  write_canvas_png(the_canvas, "test_out.png");
  free_canvas(the_canvas);
  obj_data d = init_obj_data("../data/monkey.obj");
  debug_faces(d);
  mesh_data m = init_mesh_data(d);
  free_mesh_data(m);
  free_obj_data(d);
  return 0;
}
