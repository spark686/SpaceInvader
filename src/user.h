#ifndef USER_H
#define USER_H
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
// #include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
using namespace std;

struct Attack {
    float x;
    float y;
    bool is_alive;
    Attack(float x, float y) {
        this->x = x;
        this->y = y;
        this->is_alive = true;
    }
};

struct User {
    // static GLfloat user_spaceship[6];
    vector<Attack> attacks;
    static GLfloat input_position;
    // static bool did_attack;
    bool is_alive = true;
    float x =  0.0;
    float y = -0.8;
};

#endif
