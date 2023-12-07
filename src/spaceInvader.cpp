#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
// #include <GL/glew.h>
#include <GL/glu.h>
// #include <GL/glew.h>
#include <GL/freeglut.h>
// #include <glm/glm.hpp>
// #include <glm/glm.hpp>
#include "user.h"

#include "enemies.h"
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

void display();
void input_move(int key_input, int x, int y);
void survival(int);
void input_attack(unsigned char key_input, int x, int y);
void input_mouse(int click, int state, int x, int y);
int score = 0;
int time_ingame = 30;
int counter = 0;
void update(int);
void manage_attack(int);
void populating_enemies(size_t lvl);
void create_enemies(size_t enemy_type, float pos_x);
void init_buffers();
void move_enemies();
void start_screen();
void end_lost_screen();
void end_win_screen();
void enemy_attack();
void enemies_hit();
void game_screen();
bool check_for_collision(float e_x_coord, float e_y_coord, float a_x_coord, float a_y_coord);
bool user_is_hit(float e_x_coord, float e_y_coord, float u_x_coord, float u_y_coord);
void clean_memory();

// bool is_lost;

size_t current_lvl; 
GLuint spaceship_vao;
GLuint spaceship_vbo;
GLuint enemy_vao;
GLuint enemy_vbo;
GLuint bullet_vao;
GLuint bullet_vbo;
User user;
bool is_start = true;
bool is_attack = true;
bool is_playing = true;
bool lost = false; 
vector <Enemies*> enemies; 
vector <Enemies_Type_One*> enemies_one; 
vector <Attack*> enemy_bullets;

int main(int argc, char**argv){
    current_lvl = 1;  
    populating_enemies(1);
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "error" << endl;
    //     }
    // else {
    //     cout << "no_error" << endl;
    // }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 700);

    glutCreateWindow("window");
    glClearColor(0.05f, 0.0f, 0.1f, 1.0f);

    glutKeyboardFunc(input_attack);
    glutSpecialFunc(input_move);

    glutMouseFunc(input_mouse);
    glutTimerFunc(33, update, 0);
    glutTimerFunc(300, manage_attack, 0);
    glutDisplayFunc(display);
    // GLenum error = glGetError();
    //     if (error != GL_NO_ERROR) {
    //        cout << "1error" << endl;
    //     }
    //     else {
    //        cout << "1no error" << endl;
    //     }
    glutMainLoop();
    return 0;
}

void end_lost_screen() {
    is_playing = false;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    glRasterPos2f(-0.50, 0.50);
    glColor3f(1.0f, 0.0f, 0.0f);
    const unsigned char* lost_string_literal = reinterpret_cast<const unsigned char*>("YOU LOST!");
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, lost_string_literal);

    glRasterPos2f(-1.0, 0.02);
    glColor3f(-0.20f, 1.0f, 1.0f);
    const unsigned char* start_string_literal = reinterpret_cast<const unsigned char*>("_____________________Click to restart_______________________________________");
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, start_string_literal);

}

void end_win_screen() {
    is_playing = false;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glRasterPos2f(-0.50, 0.50);
    glColor3f(-0.20f, 1.0f, 1.0f);
    const unsigned char* win_string_literal = reinterpret_cast<const unsigned char*>("YOU WON!");
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, win_string_literal);

    glRasterPos2i(-1.0, 0.02);
    glColor3f(-0.20f, 1.0f, 1.0f);
    const unsigned char* start_string_literal = reinterpret_cast<const unsigned char*>("_____________________Click to restart_______________________________________");
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, start_string_literal);

}

void start_screen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRasterPos2i(-1.0, 0.02);
    glColor3f(-0.20f, 1.0f, 1.0f);
    const unsigned char* start_string_literal = reinterpret_cast<const unsigned char*>("_____________________Click to start_______________________________________");
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, start_string_literal);
}

void init_buffers() {
    // GLfloat spaceship[6] = {
    //     +0.05f, -0.05f,
    //     -0.05f, -0.05f,
    //      0.00f, +0.05f
    // };

    GLfloat bullet[6] = {
        +0.005f, -0.005f,
        -0.005f, -0.005f,
         0.000f, +0.005f
    };

    GLfloat enemy[8] = {
       -0.05f, 0.05f,
        0.05f, 0.05f,
        0.05f, 0.0f,
       -0.05f, -0.0f
    };

    GLfloat spaceship[6] = {
        +0.05f + user.x, -0.85f,
        -0.05f + user.x, -0.85f,
        0.00f + user.x, -0.80f
    };

    //initalizng bullet, enemy, and spaceship objects
    //spaceship

    glEnableClientState(GL_VERTEX_ARRAY);
    glGenVertexArrays(1, &spaceship_vao);
    glBindVertexArray(spaceship_vao);

    glGenBuffers(1, &spaceship_vao);
    glBindBuffer(GL_ARRAY_BUFFER, spaceship_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spaceship), spaceship, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);
    
    //enemy
    glGenVertexArrays(1, &enemy_vao);
    glBindVertexArray(enemy_vao);

    glGenBuffers(1, &enemy_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, enemy_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(enemy), enemy, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);
    
    // bullet
    glGenVertexArrays(1, &bullet_vao);
    glBindVertexArray(bullet_vao);

    glGenBuffers(1, &bullet_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);
    


}

void update(int) {
    enemies_hit();
    enemy_attack();
    if(!is_start){
        counter++;
        time_ingame = 30 - counter*0.05;;
    }
    move_enemies();
    glutPostRedisplay();
    if (!user.attacks.empty()) {
        if (user.attacks.at(0).y >= 2.00) {
            user.attacks.erase(user.attacks.begin());
        }
    }
    for (Attack& attack: user.attacks) {
        attack.y += 0.01;
    }
    glutTimerFunc(33, update, 0);
}

void manage_attack(int) {
    is_attack = true;
    glutTimerFunc(300, manage_attack, 0);
}

void display(){
    if (is_start && is_playing) {
        start_screen();  
    } else if(current_lvl == 4){
        end_win_screen();
    }else if((time_ingame == 0 && score < 100) || !user.is_alive){
        end_lost_screen();
        lost = true;
    } else if(time_ingame == 0 && score > 100){
        clean_memory();
        current_lvl++; 
        score = 0; 
        counter = 0; 
        populating_enemies(current_lvl);
    } else {
        game_screen();
    }
    glutSwapBuffers();
}

void input_move(int key_input, int x,  int y) {
    if (key_input == GLUT_KEY_LEFT) {
        if(user.x > -0.8){
            user.x -= 0.1;
        }
    }
    else if (key_input == GLUT_KEY_RIGHT) {
        // User::input_position = 1;
        if(user.x < 0.8){
            user.x += 0.1;
        }
    }
}

// start button click checker
void input_mouse(int click, int state, int x, int y) {
    if ((click  == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        double x_calc = (2.0 * x) / 500.0 - 1.0;
        double y_calc = 1.0 - (2.0 * y) / 700.0;
        if ((x_calc < 0.2) && (x_calc > -0.2) && (y_calc < 0.2) && (y_calc > -0.2)) {
            if(is_start && is_playing){
                is_start = false;
                score = 0;
                is_playing = true;
                init_buffers();
                glutPostRedisplay();
            } 
            else if (lost){
                cout << "is click" << endl;
                clean_memory();
                current_lvl = 1; 
                score = 0; 
                counter = 0; 
                time_ingame = 30;
                user.is_alive = true;
                populating_enemies(current_lvl);
                lost = false;
            }
        }
    }
}

void input_attack(unsigned char key_input, int x, int y) {
    if ((key_input == 32) & is_attack) {
        user.attacks.push_back(Attack(user.x, user.y + 0.05));
        glutPostRedisplay();
        is_attack = false;
    }
}


void create_enemies(size_t enemy_type){
    if (enemy_type == 1){
        Enemies_Type_One* new_enemy = new Enemies_Type_One();
        enemies.push_back(new_enemy);
    } else if (enemy_type == 2){
        Enemies_Type_Two* new_enemy = new Enemies_Type_Two();
        enemies.push_back(new_enemy);
    } else if (enemy_type == 3){
        Enemies_Type_Three* new_enemy = new Enemies_Type_Three();
        enemies.push_back(new_enemy);
    } else {
        cout << "invalid enemy type" << endl;
    }
}

void populating_enemies(size_t type_one, size_t type_two, size_t type_three){
    for(size_t i = 0; i < type_one; i++){
    create_enemies(1);
    }
    for(size_t i = 0; i < type_two; i++){
    create_enemies(2);
    }
    for(size_t i = 0; i < type_three; i++){
    create_enemies(3);
    }
}   

void move_enemies(){
    Enemies* enemy = nullptr;
    for(size_t i = 0; i < enemies.size(); i++){
        enemy = enemies.at(i);
        enemy->enemies_movement();
    }
}

bool check_for_collision(float e_x_coord, float e_y_coord, float a_x_coord, float a_y_coord){
    if ((e_y_coord < a_y_coord) && (a_y_coord < e_y_coord + 0.05f) && (e_x_coord - 0.05f < a_x_coord) && (a_x_coord < e_x_coord + 0.05f)){
        return true;
    } else {
        return false;
    }
}

void create_enemies(size_t enemy_type, float pos_x){
    if (enemy_type == 1){
        Enemies_Type_One* new_enemy = new Enemies_Type_One();
        new_enemy->x = pos_x;
        enemies.push_back(new_enemy);
        enemies_one.push_back(new_enemy);
    } else if (enemy_type == 2){
        Enemies_Type_Two* new_enemy = new Enemies_Type_Two();
        new_enemy->x = pos_x;
        enemies.push_back(new_enemy);
    } else if (enemy_type == 3){
        Enemies_Type_Three* new_enemy = new Enemies_Type_Three();
        new_enemy->x = pos_x;
        enemies.push_back(new_enemy);
    } else {
        cout << "invalid enemy type" << endl;
    }
}

void populating_enemies(size_t lvl){
    if (lvl == 1){
        float pos_x = 0.8;
        for(size_t i = 0; i < 4; i++){
            create_enemies(1, pos_x);
            pos_x -= 0.2;
        }
        pos_x = 0.8;
        for(size_t i = 0; i < 4; i++){
            create_enemies(2, pos_x);
            pos_x -= 0.2;
        }
        pos_x = 0.8;
        for(size_t i = 0; i < 4; i++){
            create_enemies(3, pos_x);
            pos_x -= 0.2;
        }
    } 
      else if (lvl == 2){
        float pos_x = 1;
        for(size_t i = 0; i < 7; i++){
            create_enemies(1, pos_x);
            pos_x -= 0.2;
        }
        pos_x = 1;
        for(size_t i = 0; i < 7; i++){
            create_enemies(2, pos_x);
            pos_x -= 0.2;
        }
        pos_x = 1;
        for(size_t i = 0; i < 7; i++){
            create_enemies(3, pos_x);
            pos_x -= 0.2;
        }
    } else if (lvl == 3){
        float pos_x = 1.2;
        for(size_t i = 0; i < 9; i++){
            create_enemies(1, pos_x);
            pos_x -= 0.2;
        }
        pos_x = 1.2;
        for(size_t i = 0; i < 9; i++){
            create_enemies(2, pos_x);
            pos_x -= 0.2;
        }
        pos_x = 1.2;
        for(size_t i = 0; i < 9; i++){
            create_enemies(3, pos_x);
            pos_x -= 0.2;
        }
    }
}   

void enemies_hit(){
    for (size_t i = 0; i < user.attacks.size(); i++) {
            Attack* attack = &user.attacks.at(i);
            if (attack->y < 0.3){
                break;
            } 
            if(attack->is_alive){
                for(size_t i = 0; i < enemies.size(); i++){
                Enemies* enemy = enemies.at(i);
                if (enemy->is_alive){
                    if(check_for_collision(enemy->x, enemy->y, attack->x, attack->y)){
                        enemy->minus_health();
                        if(!enemy->is_alive){
                            if(enemy->type == 1){
                            enemy->is_alive = false;
                            score += 10;
                            } else if(enemy->type == 2){
                                score += 30;
                            } else {
                                score += 50;
                            }
                        }
                        attack->is_alive = false;
                    }
                }
            }
        }
    }

    for(size_t i = 0; i < enemy_bullets.size(); i++){
        Attack* attack = enemy_bullets.at(i);
        if(attack->is_alive){
            if(attack->x < 0.6){
                if(user_is_hit(attack->x, attack->y, user.x, user.y)){
                    user.is_alive = false;
                }
            }
        }
    }
}

void game_screen(){
    //print score and timer
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glRasterPos2f(0.650f, 0.90f);
    glColor3f(-0.20f, 1.0f, 1.0f);
    string score_string = to_string(score);
    score_string = "score: " + score_string;
    const char* score_literal = score_string.c_str();
    const unsigned char* score_string_literal = reinterpret_cast<const unsigned char*>(score_literal);

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, score_string_literal);

    glRasterPos2f(0.650f, 0.80f);
    glColor3f(-0.20f, 1.0f, 1.0f);
    string time_string = to_string(time_ingame);
    time_string = "time: " + time_string;
    const char* time_literal = time_string.c_str();
    const unsigned char* time_string_literal = reinterpret_cast<const unsigned char*>(time_literal);

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, time_string_literal);

    // draws user spaceship
    glPushMatrix();
    glTranslatef(user.x, user.y, 0);
    glBindVertexArray(spaceship_vao);
    glBindBuffer(GL_ARRAY_BUFFER, spaceship_vbo);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f,  0.02f); // top left
    glVertex2f(0.05f, -0.05f); // top right 
    glVertex2f(-0.05f, -0.05f); // bottom right
    glEnd();
    glPopMatrix();

    //draw enemies
    for(size_t i = 0; i < enemies.size(); i++){
        Enemies* enemy = enemies.at(i);
        if(enemy->is_alive){
            glPushMatrix();
            glTranslatef(enemy->x, enemy->y, 0);
            glBindVertexArray(enemy_vao);
            glBindBuffer(GL_ARRAY_BUFFER, enemy_vbo);
            if(enemy->type == 3){
                glColor3f(0.5f, 1.0f, 1.0f);
            } else if (enemy->type == 2){
                glColor3f(0.0f, 1.0f, 0.0f);
            } else {
                glColor3f(0.5f, 0.0f, 0.0f);
            }
            glBegin(GL_QUADS);
            glVertex2f(-0.05f, 0.05f); // top left
            glVertex2f(0.05f, 0.05f); // top right 
            glVertex2f(0.05f, 0.0f); // bottom right
            glVertex2f(-0.05f, 0.0f); // bottom left
            glEnd();
            glPopMatrix();
        }
    }

    //draws user's bullets
    for (size_t i = 0; i < user.attacks.size(); i++) {
        Attack attack = user.attacks.at(i);                    
        if(attack.is_alive){
            glPushMatrix();
            glTranslatef(attack.x, attack.y, 0);
            glBindVertexArray(bullet_vao);
            glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
            glColor3f(1.0f, 1.0f, 1.0f);
            glDrawArrays(GL_POINTS, 0, 3);
            glPopMatrix();
        }
    }

    for (size_t i = 0; i < enemy_bullets.size(); i++) {
        Attack* attack = enemy_bullets.at(i);                    
        if(attack->is_alive){
            glPushMatrix();
            glTranslatef(attack->x, attack->y, 0);
            glBindVertexArray(bullet_vao);
            glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
            glColor3f(1.0f, 1.0f, 1.0f);
            glDrawArrays(GL_POINTS, 0, 3);
            glPopMatrix();
        }
    }

}

void enemy_attack(){
    //create bullets
    if (counter % 30 == 0 && counter != 0){
        cout << time_ingame << endl;
        for(size_t i = 0; i < enemies_one.size(); i++){
            if(enemies_one.at(i)->is_alive){
                Attack* new_attack = new Attack(enemies_one.at(i)->x, enemies_one.at(i)->y);
                enemy_bullets.push_back(new_attack);
            }
        }
    }
    // moves bullets
    for (size_t i = 0; i < enemy_bullets.size(); i++) {
        Attack* bullet = enemy_bullets.at(i);            
        bullet->y -= 0.01;
    }
}

void clean_memory(){
    for(size_t i = 0; i < enemy_bullets.size(); i++){
        enemy_bullets.at(i)->is_alive = false;
    }
    for(size_t i = 0; i < enemies.size(); i++){
        enemies.at(i)->is_alive = false;
    }
    // enemy_bullets = {};
    // enemies = {};
}

bool user_is_hit(float e_x_coord, float e_y_coord, float u_x_coord, float u_y_coord){
    if ((e_y_coord < u_y_coord) && (u_y_coord < e_y_coord + 0.06f) && (e_x_coord - 0.05f < u_x_coord) && (u_x_coord < e_x_coord + 0.05f)){
        return true;
    } else {
        return false;
    }
}