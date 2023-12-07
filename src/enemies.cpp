#include <stdio.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
// #include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include "enemies.h"

using namespace std;

void Enemies::enemies_movement(){
    if(heading_left == false){
        if(x < 0.8){
            this->x += 0.01;
        } else {
            heading_left = true;
        }
    } else {
        if(x > -0.8){
            this->x -= 0.01;
        } else {
            heading_left = false;
        }
    }
    return;
}

