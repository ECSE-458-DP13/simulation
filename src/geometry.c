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
    grid_quads.vertices = (Vertex*)malloc(length*width*sizeof(quad_vertices[0])*sizeof(float));
    grid_normals.normals = (Vector*)malloc(length*width*sizeof(quad_normals[0])*sizeof(float));
    grid_elements.i = (int*)malloc(length*width*(sizeof(quad_elements)/sizeof(quad_elements[0]))*sizeof(int));

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
            //printf("ROW: %d COL: %d\n",i/10,i%10);
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

        /*printf("Q%d\n",i);
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
        printf("%d %d %d %d %d %d %d %d\n",grid_elements.i[8*i+0],grid_elements.i[8*i+1],grid_elements.i[8*i+2],grid_elements.i[8*i+3],grid_elements.i[8*i+4],grid_elements.i[8*i+5],grid_elements.i[8*i+6],grid_elements.i[8*i+7]);*/
    }
        /*printf("ALLA%d %d %d",(sizeof(quad_elements)/sizeof(quad_elements[0])),sizeof(grid_quads.vertices[0]));
    printf("asdasd %d %d %d %d %d\n",sizeof(quad_elements[0]),sizeof(quad_elements),sizeof(quad_vertices->vertices),sizeof(quad_normals),sizeof(quad_elements));
    printf("dsds %d %d %d %d\n",sizeof(float),sizeof(grid_quads),sizeof(grid_quads.vertices),sizeof(grid_quads.vertices[0]));
    printf("dsds %d %d %d\n",sizeof(grid_elements),sizeof(grid_elements.i),sizeof(grid_elements.i[0]));*/
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

// .obj Models
struct
{
    Vertex* vertices;
} obj_vertices;

struct
{
    Vector* normals;
} obj_normals;

struct
{
    int* i;
} obj_elements;


// Load .obj model
// vertices, (normals optional), faces
// Assume all faces are triangles.
char** load_obj_model(char* file_path){
    FILE* objFileHandle;
    int lengthOfObjFile = -1;
    objFileHandle = fopen(file_path, "r");
    if(objFileHandle != NULL){
        fseek(objFileHandle, 0, SEEK_END);
        lengthOfObjFile = ftell(objFileHandle);
        fclose(objFileHandle);
    }

    objFileHandle = fopen(file_path,"r");

    int total_vertices = 1;
    int total_faces = 1;
    char c;
obj_vertices.vertices = NULL;
    while((c = fgetc(objFileHandle)) != EOF){
        const char* currentchar = c;
        const char* newline = "\n";
        const char* space = " ";
        const char* o = 'o';
        const char* v = 'v';
        const char* n = 'n';
        const char* f = 'f';

        if (c == 'v') {
            c = fgetc(objFileHandle);
            
            // ignore other lines for now.
            if(c != ' '){
                while(c != '\n'){
                    c = fgetc(objFileHandle);
                }
                continue;
            }


            /*obj_vertices.vertices = (Vertex*)realloc(obj_vertices.vertices,(1));

            obj_vertices.vertices[0].x = 1.0f;         
            obj_vertices.vertices[0].y = 1.0f;   
            obj_vertices.vertices[0].z = 1.0f;    
            obj_vertices.vertices = (Vertex*)realloc(obj_vertices.vertices,(12));
            obj_vertices.vertices[1].x = 2.0f;     
            obj_vertices.vertices[1].y = 1.0f; 
            obj_vertices.vertices[1].z = 1.0f; 
            printf("%f %f %f\n",obj_vertices.vertices[1].x,obj_vertices.vertices[1].y,obj_vertices.vertices[1].z);

            return NULL;*/
            //printf("total_vertices: %d %d\n",total_vertices,sizeof(obj_vertices.vertices[0]));
            printf("%d\n",total_vertices*sizeof(obj_vertices.vertices));
//total_vertices++;
            obj_vertices.vertices = (Vertex*)realloc(obj_vertices.vertices,((total_vertices)*sizeof(Vertex)+sizeof(*obj_vertices.vertices)));
            if(obj_vertices.vertices == NULL){
                return;
            }
            /*printf("%f %f %f\n",obj_vertices.vertices[0].x,obj_vertices.vertices[0].y,obj_vertices.vertices[0].z);
            printf("test");
            printf("%f %f %f\n",obj_vertices.vertices[1].x,obj_vertices.vertices[1].y,obj_vertices.vertices[1].z);
            printf("%d total_vertices: %d\n%d%d\n",sizeof(Vertex),total_vertices,sizeof(obj_vertices.vertices),sizeof(float));*/
            total_vertices++;
            int count = 1;
            int xyz = 0;
            char* temp = NULL;
            while(c != '\n'){    
                c = fgetc(objFileHandle);
                if(c == ' ' | c == '\n'){
                    const char* floatvalue = temp;
                    float coordinate = atof(floatvalue);

                    switch(xyz){
                        case 0:
                            obj_vertices.vertices[total_vertices-1].x = coordinate;
                            break;
                        case 1:
                            obj_vertices.vertices[total_vertices-1].y = coordinate;
                            break;
                        default:
                        case 2:
                            obj_vertices.vertices[total_vertices-1].z = coordinate;
                            break;
                    }
                    
                    free(temp);
                    temp = NULL;
                    count = 1;
                    xyz++;
                    printf("%f ",coordinate);
                }
                temp = (char*)realloc(temp, count);
                temp[count-1] = c;
                count++;
            }
            printf("\n");
        } /*else if(c == 'f') {
            c = fgetc(objFileHandle);

            // ignore other lines for now.
            if(c != ' '){
                while(c != '\n'){
                    c = fgetc(objFileHandle);
                }
                continue;
            }

            int count = 1;
            char* temp = NULL;
            while(c != '\n'){
                c = fgetc(objFileHandle);
                if(c == ' ' | c == '\n'){
                    const char* intvalue = temp;
                    int element = atoi(intvalue);
                    // we ignore the face values for normals here.
                    //printf("%s %d ",intvalue,element);
                    free(temp);
                    temp = NULL;
                    count = 1; 
                    printf("%d ",element);
                }
                temp = (char*)realloc(temp, count);
                temp[count-1] = c;
                count++;
            }
            printf("\n");
        }*/
    }

    return;

    //load file
    /*FILE* labelFileHandle;
    int lengthOfFile = -1;    

    if(argc == 4 && atoi(argv[2]) > 1 && atoi(argv[3]) >= 1 && atoi(argv[3]) <= 7 && lengthOfFile > 0 && lengthOfFile <= 256){}

    if(argc == 4){
        labelFileHandle = fopen(argv[1], "r");
        if(labelFileHandle != NULL){
            fseek(labelFileHandle, 0, SEEK_END);
            lengthOfFile = ftell(labelFileHandle);
            fclose(labelFileHandle);
        } else {
            goto fileerror;
        }
    }

    labelFileHandle = fopen(argv[1],"r");

        unsigned int maxwkcount = 0;
        unsigned int line_count = 0;
        unsigned int counter = 0;
        const char space[2] = " ";
        char* days[7];
        char* months[12];
        char line[257];
        char* token;
        while(fgets(line, sizeof(line), labelFileHandle)){
            if(line_count == 0){
                token = strtok(line, space);
                for(i; i < 7; i++){
                    if(token != NULL){
                        days[counter] = malloc(strlen(token)+1);
                        if(days[counter] == NULL){ fclose(labelFileHandle); goto mallocerror; }
                        token[strcspn(token, "\n")] = 0;
                        strcpy(days[counter], token);
                    } else {
                        fclose(labelFileHandle);
                        goto fileerror;
                    }
                    maxwkcount += strlen(token);
                    token = strtok(NULL, space);
                    counter++;
                }
                counter = 0;
                i=0;
                line_count++;
            } else if (line_count == 1){
                token = strtok(line, space);
                for(i; i < 12; i++){
                    if(token != NULL){
                        months[counter] = malloc(strlen(token)+1);
                        if(months[counter] == NULL){ fclose(labelFileHandle); goto mallocerror; }
                        token[strcspn(token, "\n")] = 0;
                        strcpy(months[counter], token);
                    } else {
                        fclose(labelFileHandle);
                        goto fileerror;
                    }
                    token = strtok(NULL, space);
                    counter++;
                }
                counter = 0;
                i=0;
            }
        }
        fclose(labelFileHandle);

unsigned int line_count = 0;
    unsigned int space_count = 0;
    char c;
    while((c = fgetc(labelFileHandle)) != EOF){
        const char* c1 = &c;
        const char* c2 = "\n";
        const char* c3 = " ";    
            
        if(strncmp(c1,c2,1) == 0){
            printf(" ");
            space_count = 0;
            line_count++;
        } else if(strncmp(c1,c3,1) == 0){
            space_count++;
            continue;
        }

        if(line_count == 0 && space_count == day){
            if(strncmp(c1,c2,1) != 0 && strncmp(c1,c3,1) != 0){
                printf("%c",c);
            }
        } else if (line_count == 1 && space_count == month){
            if(strncmp(c1,c2,1) != 0 && strncmp(c1,c3,1) != 0){
                printf("%c",c);
            }
        }
        
    }
    fclose(labelFileHandle);*/

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
