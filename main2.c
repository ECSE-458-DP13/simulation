//#include <glad/glad.h>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>

#include "shaders.h"
#include "camera.h"
#include "geometry.h"
#include "physics.h"

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 M;\n"
"uniform mat4 V;\n"
"uniform mat4 P;\n"
"uniform mat3 MinvT;\n"
"in vec4 position;\n" 
"in vec3 normal;\n"
"out vec3 positionForFP;\n"
"varying vec3 normalForFP;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    vec4 posV = V * M * position;\n"
"    vec4 tmp = V * vec4( MinvT * normal, 0 );\n"
"    normalForFP = normalize( tmp.xyz );\n"
"    positionForFP = posV.xyz;\n"
"    gl_Position = P * posV;\n"
"    color = vec3(1.0,1.0,0.0);\n"
"}\n";
//vec2 vPos
//gl_Position 0.0,1.0
//color = vCol;

static const char* fragment_shader_text =
"#version 110\n"
"uniform vec3 ambient = vec3(1.0f,1.0f,1.0f);\n"
"uniform vec3 lightCol = vec3(1.0f,1.0f,1.0f);\n"
"uniform vec3 lightDir = vec3(1.0f,0.0f,0.0f);\n"
"uniform vec3 halfVec = vec3(0.0f, 0.0f, 1.0f);\n"
"uniform float shine = 1.0f;\n"
"uniform float strength = 0.5f;\n"
"//uniform vec4 kd;\n"
"varying vec3 normalForFP;\n"
"//out vec4 fragColor;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"float diffuseAmount = max(0.0, dot(normalForFP, lightDir));\n"
"float specularAmount = max(0.0, dot(normalForFP, halfVec));\n"
"if(diffuseAmount == 0.0){\n"
"    specularAmount = 0.0;\n"
"} else {\n"
"    specularAmount = pow(specularAmount, shine);\n"
"}\n"
"vec3 scatteredLight = ambient + lightCol * diffuseAmount;\n"
"vec3 reflectedLight = lightCol * specularAmount * strength;\n"
"//kd.rgb for color\n"
"vec3 rgb = min(color * scatteredLight + reflectedLight, vec3(1.0));\n"
"//fragColor = vec4(rgb, kd.a);\n"
"//kd.a\n"
"    gl_FragColor = vec4(rgb, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//static GLuint mesh;
//static GLuint mesh_vbo[2];

int main(int argc, char* argv[])
{
    printf("ECSE458 CICMR Simulation\n");
    //printf("%d %c\n",robot.i,robot.s);
    //return 0;

    GLFWwindow* window;
    GLuint mesh, mesh_vbo[2], vertex_shader, fragment_shader, program;
    GLint m_location, minvt_location, v_location, p_location, position_location, normal_location, color_location;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 16);

    window = glfwCreateWindow(640, 480, "ECSE458 CICMR Simulation", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glEnable(GL_MULTISAMPLE);
    //glClearColor(0.25f,0.5f,0.75f,1.0f);
    /*glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE_LOOP);*/

    // NOTE: OpenGL error checks have been omitted for brevity

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glUseProgram(program);

    m_location = glGetUniformLocation(program, "M");
    minvt_location = glGetUniformLocation(program, "Minvt");
    v_location = glGetUniformLocation(program, "V");
    p_location = glGetUniformLocation(program, "P");
    position_location = glGetAttribLocation(program, "position");
    normal_location = glGetAttribLocation(program, "normal");
    color_location = glGetAttribLocation(program, "color");

    init_grid(10,10);

///////////
    glGenVertexArrays(1, &mesh);
    glGenBuffers(3, mesh_vbo);
    glBindVertexArray(mesh);
    

    /*load_obj_model("./models/quad.obj");
//obj_vertices.vertices;
//obj_elements.i;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vbo[1]);
    printf("%d %d\n",total_faces,total_vertices);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj_elements.i[0])*8*total_faces,obj_elements.i,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(obj_vertices.vertices)*8*total_vertices, obj_vertices.vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(position_location);
    glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[2]);
glBufferData(GL_ARRAY_BUFFER, sizeof(obj_normals.normals)*8*total_normals, obj_normals.normals, GL_STATIC_DRAW);

    glEnableVertexAttribArray(normal_location);
    glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE, 0, 0);*/
///////////



    glBindBuffer(GL_ARRAY_BUFFER,0);

    int mul = 100;
    /*printf("aa%d\n",sizeof(quad_elements));
    printf("%d\n",sizeof(grid_elements.i[0]));
    printf("%d\n",sizeof(grid_elements.i));
    printf("%d\n",sizeof(grid_elements));
    printf("%d\n",sizeof(grid_elements.i[0])*8*mul);*/

//sizeof(grid_elements.i[0])*
    for(int i = 0; i < 8*mul; i+=8){
        printf("i: %d elements: %d %d %d %d %d %d %d %d\n",i,grid_elements.i[i],grid_elements.i[i+1],grid_elements.i[i+2],grid_elements.i[i+3],grid_elements.i[i+4],grid_elements.i[i+5],grid_elements.i[i+6],grid_elements.i[i+7]);
    }

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grid_elements.i[0])*8*mul,grid_elements.i,GL_STATIC_DRAW); //grid_elements.i[200], GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[0]);
//            printf("%f %f %f\n",grid_quads.vertices[196].x,grid_quads.vertices[196].y,grid_quads.vertices[196].z);//&grid_quads.vertices[196]
    printf("ASD %d %d \n",sizeof(grid_quads.vertices)*4*(mul+1),sizeof(grid_quads.vertices));
    //printf("%d\n",sizeof(quad_vertices.vertices));
    int size = sizeof(grid_quads.vertices)*8*(mul+1);
    printf("%dsss%d\n",sizeof(quad_vertices),size);
    //int size = 48;
    glBufferData(GL_ARRAY_BUFFER, size, grid_quads.vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(position_location);
        glVertexAttribPointer(position_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
//glBindBuffer(GL_ARRAY_BUFFER,0);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, minv, minvt, v, p;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4x4_identity(m);
        //mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_invert(minv,m);
        mat4x4_transpose(minvt,minv);

        vec3 eye = {0,5,-1};
        vec3 center = {0,0,0};
        vec3 up = {0,1,0};

        mat4x4_look_at(v,eye,center,up);
        //ratio = 1.0f/ratio;
        float fov_y = 3.0f;
        float near = 0.1f;
        float far = 450.0f;
        mat4x4_perspective(p, ratio, fov_y, near, far);

        glUseProgram(program);

        glUniformMatrix4fv(m_location, 1, GL_FALSE, (const GLfloat*) m);
        glUniformMatrix4fv(minvt_location, 1, GL_FALSE, (const GLfloat*) minvt);
        glUniformMatrix4fv(v_location, 1, GL_FALSE, (const GLfloat*) v);
        glUniformMatrix4fv(p_location, 1, GL_FALSE, (const GLfloat*) p);

        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        //glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);
//        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);
        
//old grid
glDrawElements(GL_LINES, (mul+1)*8, GL_UNSIGNED_INT, 0);
// sphere?
        //glDrawElements(GL_TRIANGLES,total_faces+10,GL_UNSIGNED_INT,(void*)0);
        //glDrawArrays(GL_TRIANGLE_FAN,0,(total_vertices+1)*8);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete_grid();

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
