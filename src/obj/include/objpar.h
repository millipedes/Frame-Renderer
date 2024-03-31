/**
*
*      Copyright � 2000 Felipe Alfonso <felipe@voidptr.io>
*      This work is free. You can redistribute it and/or modify it under the
*      terms of the Do What The Fuck You Want To Public License, Version 2,
*      as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
*
*
* objpar
* ======
*
* Simple Wavefront OBJ parser.
* 
* Currently it depends on stdlib's atoi and atof. You can provide your own implementation
* by doing 
*
* `#define objpar_atoi my_atoi`
* `#define objpar_atof my_atof`
*
* For now it only supports:
* - Geometric Vertices.
* - Vertex Normals.
* - Texture Vertices
* - Faces
*
* The function objpar_build_mesh will generate a flat array containing the vertex data
* for the specified objpar_data structure.
*
* The vertex structure will depend on which parameters are stored on the parsed obj file.
* Here is how it would look for a file with position, normals and texture coordinates.
* 
* struct vertex
* {
*     float position[POSITION_WIDTH];
*     float texcoord[TEXCOORD_WIDTH];
*     float normals[NORMALS_WIDTH];
* };
* 
* The objpar_mesh structure will provide the data, vertex stride, vertex count, position,
* texcoord and normal offsets. With this information you can define your vertex input 
* layout for different graphics API. If an offset has a value of -1 it means that it's 
* not part of the vertex.
* 
*
* Repo: https://github.com/bitnenfer/objpar/
*
* -------------------------------------------------------------------------------
* Wavefront OBJ Format Specification: http://www.martinreddy.net/gfx/3d/OBJ.spec
*/

#ifndef _OBJPAR_H_
#define _OBJPAR_H_

#if __cplusplus
extern "C" 
{
#endif

#if !defined(objpar_atoi) || !defined(objpar_atof)
#include <stdlib.h>
#define objpar_atoi atoi
#define objpar_atof (float)atof
#endif

#define OBJPAR_NULL(type) ((type*)0)

#define OBJPAR_V_IDX 0
#define OBJPAR_VT_IDX 1
#define OBJPAR_VN_IDX 2
#define objpar_get_size(string, string_size) objpar((const char*)string, string_size, NULL, NULL)
#define objpar_get_mesh_size(obj_data) objpar_build_mesh(obj_data, NULL, NULL)

#include <assert.h>
#include <stdio.h>

typedef struct objpar_data
{
    /* Data */
    float* p_positions;
    float* p_texcoords;
    float* p_normals;
    unsigned int* p_faces;
    
    /* Sizes */
    unsigned int position_count;
    unsigned int normal_count;
    unsigned int texcoord_count;
    unsigned int face_count;
    unsigned int position_width;
    unsigned int normal_width;
    unsigned int texcoord_width;
    unsigned int face_width;

} objpar_data_t;

typedef struct objpar_mesh
{
    void* p_vertices;
    unsigned int vertex_count;
    unsigned int vertex_stride;
    int position_offset;
    int texcoord_offset;
    int normal_offset;
} objpar_mesh_t;

unsigned int objpar(const char* p_string, unsigned int string_size, void* p_buffer, struct objpar_data* p_data);
unsigned int objpar_build_mesh(const struct objpar_data* p_data, void* p_buffer, struct objpar_mesh* p_mesh);
unsigned int objpar_internal_v(const char* p_string, unsigned int* p_index, unsigned int string_size, float** pp_vbuff, unsigned int vertex_width);
unsigned int objpar_internal_vn(const char* p_string, unsigned int* p_index, unsigned int string_size, float** pp_nbuff, unsigned int normal_width);
unsigned int objpar_internal_vt(const char* p_string, unsigned int* p_index, unsigned int string_size, float** pp_tbuff, unsigned int texcoord_width);
unsigned int objpar_internal_f(const char* p_string, unsigned int* p_index, unsigned int string_size, unsigned int** pp_fbuff, unsigned int face_width);
unsigned int objpar_internal_comment(const char* p_string, unsigned int* p_index);
unsigned int objpar_internal_newline(const char* p_string, unsigned int* p_index, unsigned int* p_space_count);
void* open_file(const char* p_file_name, size_t* p_file_size);


#endif /* _OBJPAR_H_ */

