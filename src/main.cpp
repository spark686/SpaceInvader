#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

void display();

int main(int argc, char**argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize(500, 500);

    glutCreateWindow("window");
    glClearColor(0.1f, 0.0f, 0.5f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //draw
    GLfloat triangle_vertices[] = {
        -0.3f, 0.3f,
        0.3f, 0.3f,
        0.0f, -0.3f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    //dislays
    glFlush();
}