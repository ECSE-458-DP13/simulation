#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Triangle
struct
{
    float x, y, z;
} triangle_vertices[3] =
{
    { -1,-1, 0 },
    { 1,-1, 0 },
    { -1, 1, 0 }
};

struct
{
    float x, y, z;
} triangle_normals[3] =
{
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 }
};

struct
{
    int i;
} triangle_elements[3] =
{
    { 0 },
    { 1 },
    { 2 }
};

// Quad
struct
{
    float x, y, z;
} quad_vertices[4] =
{
    { -0.5,0, -0.5 },
    { 0.5,0, -0.5 },
    { -0.5, 0, 0.5 },
    { 0.5, 0, 0.5 }
};

struct
{
    float x, y, z;
} quad_normals[4] =
{
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 }
};

struct
{
    int i;
} quad_elements[4] =
{
    { 0 },
    { 2 },
    { 3 },
    { 1 }
};

// Cube
struct
{
    float x, y, z;
} cube_vertices[24] =
{
    { -1,-1, 0 },
    { 1,-1, 0 },
    { -1, 1, 0 },
    { 1, 1, 0 },

    { -1,-1, -1 },
    { 1,-1, -1 },
    { -1, 1, -1 },
    { 1, 1, -1 },

    { -1, 1, 0 },
    { 1, 1, 0 },
    { -1, 1, -1 },
    { 1, 1, -1 },

    { -1, -1, 0 },
    { 1, -1, 0 },
    { -1, -1, -1 },
    { 1, -1, -1 },

    { -1,-1, 0 },
    { -1,-1, -1 },
    { -1, 1, -1 },
    { -1, 1, 0 },

    { 1,-1, 0 },
    { 1,-1, -1 },
    { 1, 1, -1 },
    { 1, 1, 0 }
};

struct
{
    float x, y, z;
} cube_normals[24] =
{
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 },

    { 0, 0, -1 },
    { 0, 0, -1 },
    { 0, 0, -1 },
    { 0, 0, -1 },

    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },

    { 0, -1, 0 },
    { 0, -1, 0 },
    { 0, -1, 0 },
    { 0, -1, 0 },

    { 1, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 0 },

    { -1, 0, 0 },
    { -1, 0, 0 },
    { -1, 0, 0 },
    { -1, 0, 0 }
};

struct
{
    int i;
} cube_elements[24] =
{
    { 0 },
    { 1 },
    { 2 },
    { 3 },

    { 4 },
    { 5 },
    { 6 },
    { 7 },

    { 8 },
    { 9 },
    { 10 },
    { 11 },

    { 12 },
    { 13 },
    { 14 },
    { 15 },

    { 16 },
    { 17 },
    { 18 },
    { 19 },

    { 20 },
    { 21 },
    { 22 },
    { 23 },
};

// Cylinder
struct
{
    float x, y, z;
} cylinder_vertices[3] =
{
    { -1,-1, 0 },
    { 1,-1, 0 },
    { -1, 1, 0 }
};

struct
{
    float x, y, z;
} cylinder_normals[3] =
{
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 }
};

struct
{
    int i;
} cylinder_elements[3] =
{
    { 0 },
    { 1 },
    { 2 }
};

// Sphere
struct
{
    float x, y, z;
} sphere_vertices[3] =
{
    { -1,-1, 0 },
    { 1,-1, 0 },
    { -1, 1, 0 }
};

struct
{
    float x, y, z;
} sphere_normals[3] =
{
    { 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 }
};

struct
{
    int i;
} sphere_elements[3] =
{
    { 0 },
    { 1 },
    { 2 }
};

// Load .obj model
// vertices, normals, faces
char** load_obj_model(char* file_path){
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "sssss");
   printf("String = %s,  Address = %u\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, "test");
   printf("String = %s,  Address = %u\n", str, str);

   free(str);
}
