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

    glutInitWindowSize(200, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("window");
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //draw
    //dislays
    glFlush();
}