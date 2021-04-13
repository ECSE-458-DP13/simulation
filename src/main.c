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
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec3 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
"    color = vec3(1.0,1.0,0.0);\n"
"}\n";
//vec2 vPos
//gl_Position 0.0,1.0
//color = vCol;

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
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

static GLuint mesh;
static GLuint mesh_vbo[2];

int main(int argc, char* argv[])
{
    printf("ECSE458 CICMR Simulation\n");
    //printf("%d %c\n",robot.i,robot.s);
    //return 0;

    GLFWwindow* window;
    GLuint vertex_buffer, normal_buffer, element_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

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

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glGenVertexArrays(1, &mesh);
    glGenBuffers(2, mesh_vbo);
    glBindVertexArray(mesh);

    int rows = 3;
    int columns = 3;
    init_grid(rows,columns);

    //glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grid_elements.i[0])*8*rows*columns,grid_elements.i,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grid_quads.vertices)*8*rows*columns, grid_quads.vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glBindBuffer(GL_ARRAY_BUFFER,0);


    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, v, p, mvp, t;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4x4_identity(m);
        //mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

        vec3 eye = {0,5,-1};
        vec3 center = {0,0,0};
        vec3 up = {0,1,0};

        mat4x4_look_at(v,eye,center,up);
        //ratio = 1.0f/ratio;
        float fov_y = 3.0f;
        float near = 0.1f;
        float far = 450.0f;
        mat4x4_perspective(p, ratio, fov_y, near, far);
        mat4x4_mul(mvp, v, m);
        mat4x4_mul(mvp, p, mvp);
        //t[2][3] = 0.9f;
        //mat4x4_add(mvp,mvp,t);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        //glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);
//        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);
        
//old grid
glDrawElements(GL_LINES, (rows*columns)*8, GL_UNSIGNED_INT, 0);
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
