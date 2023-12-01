#include <iostream> 
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
    cout << "invalid enemies type" << endl;
    return;
}

void Enemies_Type_One::enemies_movement(){
    if(heading_left == false){
        if(x < 0.8){
            this->x += 0.02;
        } else {
            heading_left = true;
        }
    } else {
        if(x > -0.8){
            this->x -= 0.02;
        } else {
            heading_left = false;
        }
    }
    return;
}

void Enemies_Type_Two::enemies_movement(){
    if(heading_left == false){
        if(x < 0.8){
            this->x += 0.04;
        } else {
            heading_left = true;
        }
    } else {
        if(x > -0.8){
            this->x -= 0.04;
        } else {
            heading_left = false;
        }
    }
    return;
}

void Enemies_Type_Three::enemies_movement(){
    if(heading_left == false){
        if(x < 0.8){
            this->x += 0.06;
        } else {
            heading_left = true;
        }
    } else {
        if(x > -0.8){
            this->x -= 0.06;
        } else {
            heading_left = false;
        }
    }
    return;
}
