#ifndef GEOMETRY_H
#define GEOMETRY_H

// Vertex and Vector
typedef struct 
{
    float x, y, z;
} Vertex, Vector;

// Triangle
extern struct
{
    Vertex vertices[3];
} triangle_vertices;

extern struct
{
    Vector normals[3];
} triangle_normals;

extern struct
{
    int i;
} triangle_elements[3];

// Quad
extern struct
{
    Vertex vertices[4];
} quad_vertices;

extern struct
{
    Vector normals[4];
} quad_normals;

extern struct
{
    int i;
} quad_elements[4];

// Grid
extern struct
{
    Vertex vertices;
} *grid_vertices;

extern struct
{
    Vector normals;
} *grid_normals;

extern struct
{
    int i;
} *grid_elements;

void init_grid(int length, int width);

// Cube
extern struct
{
    Vertex vertices[24];
} cube_vertices;

extern struct
{
    Vector normals[24];
} cube_normals;

extern struct
{
    int i;
} cube_elements[24];

// Cylinder
extern struct
{
    Vertex vertices[24];
} cylinder_vertices;

extern struct
{
    Vector normals[24];
} cylinder_normals;

extern struct
{
    int i;
} cylinder_elements[24];

// Sphere
extern struct
{
    Vertex vertices[24];
} sphere_vertices;

extern struct
{
    Vector normals[24];
} sphere_normals;

extern struct
{
    int i;
} sphere_elements[24];

// Load .obj model
// vertices, normals, faces
char** load_obj_model(char* file_path);

#endif


