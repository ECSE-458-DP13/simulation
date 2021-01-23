#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vertex and Vector
typedef struct 
{
    float x, y, z;
} Vertex, Vector;

// Triangle
struct
{
    Vertex vertices[3];
} triangle_vertices =
{
    {{ -1,0, -1 },
    { 1,0, -1 },
    { 0, 0, 1 }}
};

struct
{
    Vector normals[3];
} triangle_normals =
{
    {{ 0,1, 0 },
    { 0,1, 0 },
    { 0, 1, 0 }}
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
    Vertex vertices;
} quad_vertices[4] =
{
    { -0.5,0, -0.5 },
    { 0.5,0, -0.5 },
    { -0.5, 0, 0.5 },
    { 0.5, 0, 0.5 }
};

struct
{
    Vector normals;
} quad_normals[4] =
{
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 }
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

// Grid
struct
{
    Vertex vertices[4];
} *grid_quads;

struct
{
    Vector normals[4];
} *grid_normals;

struct
{
    int i[4];
} *grid_elements;

void init_grid(int length, int width){
    grid_quads = (Vertex*)malloc(length*width*sizeof(quad_vertices));
    grid_normals = (Vector*)malloc(length*width*sizeof(quad_normals));
    grid_elements = (int*)malloc(length*width*sizeof(quad_elements));
    for(int i = 0; i < length*width; i++){
        //grid_vertices[i].vertices[0].x

        memcpy(grid_quads[i].vertices,quad_vertices,sizeof(quad_vertices));
        memcpy(grid_normals[i].normals,quad_normals,sizeof(quad_normals));
        memcpy(grid_elements[i].i,quad_elements,sizeof(quad_elements));
        //memcpy(grid_normals[i].normals,quad_normals.normals,4);
        //grid_vertices[i].vertices = quad_vertices.vertices;
        //grid_normals[i].normals = quad_normals.normals;
        //grid_elements[i] = quad_elements;
        //memcpy(grid_elements,quad_elements,4);
    }

    for(int i = 0; i < length*width; i++){
        if(i < 50){
            grid_quads[i].vertices[0].x-=(49-i)/2;
            grid_quads[i].vertices[0].z-=(49-i)/2;
            grid_quads[i].vertices[1].x-=(49-i)/2;
            grid_quads[i].vertices[1].z-=(49-i)/2;
            grid_quads[i].vertices[2].x-=(49-i)/2;
            grid_quads[i].vertices[2].z-=(49-i)/2;
            grid_quads[i].vertices[3].x-=(49-i)/2;
            grid_quads[i].vertices[3].z-=(49-i)/2;
        } else {
            grid_quads[i].vertices[0].x+=(i-49)/2;
            grid_quads[i].vertices[0].z+=(i-49)/2;
            grid_quads[i].vertices[1].x+=(i-49)/2;
            grid_quads[i].vertices[1].z+=(i-49)/2;
            grid_quads[i].vertices[2].x+=(i-49)/2;
            grid_quads[i].vertices[2].z+=(i-49)/2;
            grid_quads[i].vertices[3].x+=(i-49)/2;
            grid_quads[i].vertices[3].z+=(i-49)/2;
        }
        printf("Q%d\n",i);
        printf("%f %f %f\n",grid_quads[i].vertices[0].x,grid_quads[i].vertices[0].y,grid_quads[i].vertices[0].z);
        printf("%f %f %f\n",grid_quads[i].vertices[1].x,grid_quads[i].vertices[1].y,grid_quads[i].vertices[1].z);
        printf("%f %f %f\n",grid_quads[i].vertices[2].x,grid_quads[i].vertices[2].y,grid_quads[i].vertices[2].z);
        printf("%f %f %f\n",grid_quads[i].vertices[3].x,grid_quads[i].vertices[3].y,grid_quads[i].vertices[3].z);
        printf("%d\n",i);
        printf("%f %f %f\n",grid_normals[i].normals[0].x,grid_normals[i].normals[0].y,grid_normals[i].normals[0].z);
        printf("%f %f %f\n",grid_normals[i].normals[1].x,grid_normals[i].normals[1].y,grid_normals[i].normals[1].z);
        printf("%f %f %f\n",grid_normals[i].normals[2].x,grid_normals[i].normals[2].y,grid_normals[i].normals[2].z);
        printf("%f %f %f\n",grid_normals[i].normals[3].x,grid_normals[i].normals[3].y,grid_normals[i].normals[3].z);
        printf("%d\n",i);
        printf("%d %d %d %d\n",grid_elements[i].i[0],grid_elements[i].i[1],grid_elements[i].i[2],grid_elements[i].i[3]);
    }
}

void delete_grid(){
    free(grid_quads);
    free(grid_normals);
    free(grid_elements);
}

// Cube
struct
{
    Vertex vertices[24];
} cube_vertices =
{
    {{ -1,-1, 0 },
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
    { 1, 1, 0 }}
};

struct
{
    Vector normals[24];
} cube_normals =
{
    {{ 0, 0, 1 },
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
    { -1, 0, 0 }}
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
    Vertex vertices[3];
} cylinder_vertices =
{
    {{ -1,-1, 0 },
    { 1,-1, 0 },
    { -1, 1, 0 }}
};

struct
{
    Vector normals[3];
} cylinder_normals =
{
    {{ 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 }}
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
    Vertex vertices[3];
} sphere_vertices =
{
    {{ -1,-1, 0 },
    { 1,-1, 0 },
    { -1, 1, 0 }}
};

struct
{
    Vector normals[3];
} sphere_normals =
{
    {{ 0, 0, 1 },
    { 0, 0, 1 },
    { 0, 0, 1 }}
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
