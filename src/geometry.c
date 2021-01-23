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
    { -0.5,0.0,0.5},
   {-0.5,0.0,-0.5},
   {0.5,0.0,-0.5},
   {0.5,0.0,0.5}
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
} quad_elements[8] =
{
    { 0 },
    { 1 },
    { 1 },
    { 2 },
    { 2 },
    { 3 },
    { 3 },
    { 0 }
};

// Grid
struct
{
    Vertex* vertices;
} grid_quads;

struct
{
    Vector* normals;
} grid_normals;

struct
{
    int* i;
} grid_elements;

void init_grid(int length, int width){
    grid_quads.vertices = (Vertex*)malloc(length*width*12*4);
    grid_normals.normals = (Vector*)malloc(length*width*12*4);
    grid_elements.i = (int*)malloc(length*width*8*4);
    for(int i = 0; i < length*width; i++){
        //grid_vertices[i].vertices[0].x
        //12 * 100 total
        memcpy(&grid_quads.vertices[i*4],quad_vertices,sizeof(quad_vertices));
        memcpy(&grid_normals.normals[i*4],quad_normals,sizeof(quad_normals));
        memcpy(&grid_elements.i[i*8],quad_elements,sizeof(quad_elements));
        //memcpy(grid_normals[i].normals,quad_normals.normals,4);
        //grid_vertices[i].vertices = quad_vertices.vertices;
        //grid_normals[i].normals = quad_normals.normals;
        //grid_elements[i] = quad_elements;
        //memcpy(grid_elements,quad_elements,4);
    }

    for(int i = 0; i < length*width; i++){
            grid_quads.vertices[4*i+0].x=-5.5f;
            grid_quads.vertices[4*i+0].z=5.5f;
            grid_quads.vertices[4*i+1].x=-5.5f;
            grid_quads.vertices[4*i+1].z=4.5f;
            grid_quads.vertices[4*i+2].x=-4.5f;
            grid_quads.vertices[4*i+2].z=4.5f;
            grid_quads.vertices[4*i+3].x=-4.5f;
            grid_quads.vertices[4*i+3].z=5.5f;

        /*if(i < 10){*/
            printf("ROW: %d COL: %d\n",i/10,i%10);
            grid_quads.vertices[4*i+0].x+=(int)(i%10);
            grid_quads.vertices[4*i+1].x+=(int)(i%10);
            grid_quads.vertices[4*i+2].x+=(int)(i%10);
            grid_quads.vertices[4*i+3].x+=(int)(i%10);

            grid_quads.vertices[4*i+0].z-=(int)(i/10);
            grid_quads.vertices[4*i+1].z-=(int)(i/10);
            grid_quads.vertices[4*i+2].z-=(int)(i/10);
            grid_quads.vertices[4*i+3].z-=(int)(i/10);
        /*} else {
            grid_quads.vertices[4*i+0].x+=(i-49)/2;
            grid_quads.vertices[4*i+0].z+=(i-49)/2;
            grid_quads.vertices[4*i+1].x+=(i-49)/2;
            grid_quads.vertices[4*i+1].z+=(i-49)/2;
            grid_quads.vertices[4*i+2].x+=(i-49)/2;
            grid_quads.vertices[4*i+2].z+=(i-49)/2;
            grid_quads.vertices[4*i+3].x+=(i-49)/2;
            grid_quads.vertices[4*i+3].z+=(i-49)/2;
        }*/
        grid_elements.i[8*i+0]+=4*i;
        grid_elements.i[8*i+1]+=4*i;
        grid_elements.i[8*i+2]+=4*i;
        grid_elements.i[8*i+3]+=4*i;
        grid_elements.i[8*i+4]+=4*i;
        grid_elements.i[8*i+5]+=4*i;
        grid_elements.i[8*i+6]+=4*i;
        grid_elements.i[8*i+7]+=4*i;
        /*grid_elements.i[8*i+0]-=200;
        grid_elements.i[8*i+1]-=200;
        grid_elements.i[8*i+2]-=200;
        grid_elements.i[8*i+3]-=200;
        grid_elements.i[8*i+4]-=200;
        grid_elements.i[8*i+5]-=200;
        grid_elements.i[8*i+6]-=200;
        grid_elements.i[8*i+7]-=200;*/
        printf("Q%d\n",i);
        printf("%f %f %f\n",grid_quads.vertices[4*i+0].x,grid_quads.vertices[4*i+0].y,grid_quads.vertices[4*i+0].z);
        printf("%f %f %f\n",grid_quads.vertices[4*i+1].x,grid_quads.vertices[4*i+1].y,grid_quads.vertices[4*i+1].z);
        printf("%f %f %f\n",grid_quads.vertices[4*i+2].x,grid_quads.vertices[4*i+2].y,grid_quads.vertices[4*i+2].z);
        printf("%f %f %f\n",grid_quads.vertices[4*i+3].x,grid_quads.vertices[4*i+3].y,grid_quads.vertices[4*i+3].z);
        printf("%d\n",i);
        printf("%f %f %f\n",grid_normals.normals[4*i+0].x,grid_normals.normals[4*i+0].y,grid_normals.normals[4*i+0].z);
        printf("%f %f %f\n",grid_normals.normals[4*i+1].x,grid_normals.normals[4*i+1].y,grid_normals.normals[4*i+1].z);
        printf("%f %f %f\n",grid_normals.normals[4*i+2].x,grid_normals.normals[4*i+2].y,grid_normals.normals[4*i+2].z);
        printf("%f %f %f\n",grid_normals.normals[4*i+3].x,grid_normals.normals[4*i+3].y,grid_normals.normals[4*i+3].z);
        printf("%d\n",i);
        printf("%d %d %d %d %d %d %d %d\n",grid_elements.i[8*i+0],grid_elements.i[8*i+1],grid_elements.i[8*i+2],grid_elements.i[8*i+3],grid_elements.i[8*i+4],grid_elements.i[8*i+5],grid_elements.i[8*i+6],grid_elements.i[8*i+7]);
    }
    printf("asdasd %d %d %d\n",sizeof(quad_vertices[0]),sizeof(quad_normals),sizeof(quad_elements));
}

void delete_grid(){
    free(grid_quads.vertices);
    free(grid_normals.normals);
    free(grid_elements.i);
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
