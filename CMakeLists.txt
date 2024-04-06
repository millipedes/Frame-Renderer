cmake_minimum_required(VERSION 3.12)
project(new_project)

# Source files
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(SRC_FILES
  ${SRC_DIR}/canvas/canvas.c
  ${SRC_DIR}/canvas/pixel.c
  ${SRC_DIR}/geometry_processing/vertex_shading.c
  ${SRC_DIR}/obj/objpar.c
  ${SRC_DIR}/obj/mmtl_parser.c
  ${SRC_DIR}/obj/objpar_wrapper.c
)

# Include directories
include_directories(${SRC_DIR})

# Add executable
add_executable(new_project ${SRC_FILES} ${SRC_DIR}/main/main.c)

# Link libraries
find_package(PNG REQUIRED)
target_link_libraries(new_project PNG::PNG m)
target_compile_options(new_project PRIVATE -Wall -Wextra -g)
