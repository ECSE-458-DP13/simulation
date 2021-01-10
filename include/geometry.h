#ifndef GEOMETRY_H
#define GEOMETRY_H

// Triangle
extern struct
{
    float x, y, z;
} triangle_vertices[3];

extern struct
{
    float x, y, z;
} triangle_normals[3];

extern struct
{
    int i;
} triangle_elements[3];

// Quad
extern struct
{
    float x, y, z;
} quad_vertices[4];

extern struct
{
    float x, y, z;
} quad_normals[4];

extern struct
{
    int i;
} quad_elements[4];

// Cube
extern struct
{
    float x, y, z;
} cube_vertices[24];

extern struct
{
    float x, y, z;
} cube_normals[24];

extern struct
{
    int i;
} cube_elements[24];

// Cylinder
extern struct
{
    float x, y, z;
} cylinder_vertices[24];

extern struct
{
    float x, y, z;
} cylinder_normals[24];

extern struct
{
    int i;
} cylinder_elements[24];

// Sphere
extern struct
{
    float x, y, z;
} sphere_vertices[24];

extern struct
{
    float x, y, z;
} sphere_normals[24];

extern struct
{
    int i;
} sphere_elements[24];

// Load .obj model
// vertices, normals, faces
char** load_obj_model(char* file_path);

#endif


