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
    bool is_alive;
    void enemies_movement();
    vector <Attack> attack;
    float x;
    float y;
    size_t health;
    size_t type;
    void minus_health();
    Enemies(){
        this->heading_left = false;
        this->type = 0;
        this->is_alive = true;
        this->x = 0;
        this->y = 0;
        this->health = 0;
    }
    // static bool did_attack;
};

struct Enemies_Type_One: public Enemies{
    // void enemies_movement();
    Enemies_Type_One(){
        this->heading_left = false;
        this->type = 1;
        this->is_alive = true;
        this->x = 0.0;
        this->y = 0.4;
        this->health = 1;
    }
};

struct Enemies_Type_Two: public Enemies{
    // void enemies_movement();
    Enemies_Type_Two(){
        this->heading_left = false;
        this->type = 2;
        this->is_alive = true;
        this->x = 0.0;
        this->y = 0.6;
        this->health= 2;
    }
};

struct Enemies_Type_Three: public Enemies{
    // void enemies_movement();
    Enemies_Type_Three(){
        this->heading_left = false;
        this->type = 3;
        this->is_alive = true;
        this->x = 0.0;
        this->y = 0.8;
        this->health = 3;
    }
};