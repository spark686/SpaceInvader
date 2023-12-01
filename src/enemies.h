#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
// #include <GL/glu.h>
#include <GL/glut.h>
#include "user.h"
#include <vector>
using namespace std;


struct Enemies {
    // static GLfloat user_spaceship[6];
    vector<Attack> attacks;
    static GLfloat input_position;
    bool heading_left;
    // bool is_alive = true;
    virtual void enemies_movement();
    float x;
    float y;

    Enemies(){
        this->heading_left = false;
        this->x = 0;
        this->y = 0;
    }
    // static bool did_attack;
};

struct Enemies_Type_One: public Enemies{
    void enemies_movement();
    Enemies_Type_One(){
        this->heading_left = false;
        this->x = 0.0;
        this->y = 0.4;
    }
};

struct Enemies_Type_Two: public Enemies{
    void enemies_movement();
    Enemies_Type_Two(){
        this->heading_left = false;
        this->x = 0.0;
        this->y = 0.6;
    }
};

struct Enemies_Type_Three: public Enemies{
    void enemies_movement();
    Enemies_Type_Three(){
        this->heading_left = false;
        this->x = 0.0;
        this->y = 0.8;
    }
};

