#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
// #include <GL/glew.h>
#include <GL/glu.h>
// #include <GL/glew.h>
#include <GL/freeglut.h>
// #include <glm/glm.hpp>
#include "user.h"

#include "enemies.h"
#include <cstdlib>
#include <unistd.h>
#include <vector>

using namespace std;

void display();
void input_move(int key_input, int x, int y);
void input_attack(unsigned char key_input, int x, int y);
void update(int);
// void populating_enemies(size_t type_one, size_t type_two, size_t type_three);
// void create_enemies(size_t enemy_type);
void init_buffers();
void move_enemies();
// void check_for_collision()

GLuint ship_vao;
GLuint ship_vbo;
// GLuint enemies_vao;
// GLuint enemies_vbo;
GLuint bullet_vao;
GLuint bullet_vbo;
User user;
// vector <Enemies*> enemies; 

int main(int argc, char**argv){
    // populating_enemies(1,1,1);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glutInitWindowSize(500, 700);

    glutCreateWindow("window");
    glClearColor(0.05f, 0.0f, 0.1f, 1.0f);

    // User user_;
    cout << 1 << endl;
    init_buffers();
    cout << 2 << endl;

    glutDisplayFunc(display);
    // sleep(1);
    cout << 3 << endl;

    glutKeyboardFunc(input_attack);
    cout << 4 << endl;

    glutSpecialFunc(input_move);
    cout << 5 << endl;


    glutTimerFunc(33, update, 0);
    cout << 6 << endl;

    glutMainLoop();
    cout << 7 << endl;
    return 0;
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

    // GLfloat enemies[6] = {
    //     +0.005f, -0.005f,
    //     -0.005f, -0.005f,
    //      0.000f, +0.005f
    // };

    // std::cout << glGetString(GL_VERSION) << '\n';;

    glEnableClientState(GL_VERTEX_ARRAY);

    GLuint ids[2] = {42, 42};
    glGenVertexArrays(2, ids);
    // ship_vao   = ids[0];
    bullet_vao = ids[0];
    // #version 330 core
    // vec3 a = vec3(1.0, 0.0, 0.0);

    // glBindVertexArray(enemies_vao);

    // glGenBuffers(1, &enemies_vao);
    // glBindBuffer(GL_ARRAY_BUFFER, enemies_vao);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(enemies), enemies, GL_DYNAMIC_DRAW);
    // glVertexPointer(2, GL_FLOAT, 0, nullptr);
    // glBindVertexArray(0);


    // glGenVertexArrays(1, &ship_vao);
    // glBindVertexArray(ship_vao);

    // glGenBuffers(1, &ship_vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(spaceship), spaceship, GL_DYNAMIC_DRAW);
    // glVertexPointer(2, GL_FLOAT, 0, nullptr);

    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 
    //         (GLvoid*)0);
    // glBindVertexArray(0);


    glGenVertexArrays(1, &bullet_vao);
    glBindVertexArray(bullet_vao);

    glGenBuffers(1, &bullet_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);


    std::cout << "Ship:   " << ship_vao   << ' ' << ship_vbo   << '\n';
    std::cout << "Bullet: " << bullet_vao << ' ' << bullet_vbo << '\n';
}

void update(int) {
    // move things
    // move_enemies();
    glutPostRedisplay();
    for (Attack& attack: user.attacks) {
        attack.y += 0.01;
    }

    // create attack ball if user_input == space
    glutTimerFunc(33, update, 0);
}

void display(){
    // cout << 10 << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    // cout << 11 << endl;
    glLoadIdentity();
    // cout << 12 << endl;

    //draw userspaceship  


    // glPushMatrix();
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     fprintf(stderr, "OpenGL Error: %d\n", error);
    // } 
    // else {
    //     cout << "no error" << endl;
    // }
    GLfloat spaceship[6] = {
        +0.05f + user.x, -0.85f,
        -0.05f + user.x, -0.85f,
         0.00f + user.x, -0.80f
    };

    // GLfloat color_spaceship[9] = {
    //     1.0f, 0.0f, 0.0f,
    //     1.0f, 0.0f, 0.0f,
    //     1.0f, 0.0f, 0.0f
    // };

    GLuint spaceship_vao;
    GLuint spaceship_vbo;
    // GLuint spaceship_color_vbo;
    
    glBindVertexArray(spaceship_vao);

    glGenBuffers(1, &spaceship_vao);
    glBindBuffer(GL_ARRAY_BUFFER, spaceship_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spaceship), spaceship, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);

    glGenBuffers(1, &spaceship_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, spaceship_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spaceship), spaceship, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);


    // glGenBuffers(1, &spaceship_color_vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, spaceship_color_vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(color_spaceship), color_spaceship, GL_DYNAMIC_DRAW);
    // glVertexPointer(3, GL_FLOAT, 0, nullptr);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    // glEnableVertexAttribArray(2);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);





    // glTranslatef(user.x, user.y, 0);
    // glBindVertexArray(ship_vao);
    // glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glPopMatrix();
    // finished drawing spaceship



    // glPushMatrix();
    // //draw enemies
    // // cout << 13 << endl;
    // for(size_t i = 0; i < enemies.size(); i++){
    //     Enemies* enemy = enemies.at(i);
    //     glPushMatrix();
    //     glTranslatef(enemy->x, enemy->y, 0);
    //     glBindVertexArray(enemies_vao);
    //     glBindBuffer(GL_ARRAY_BUFFER, enemies_vbo);
    //     glDrawArrays(GL_POINTS, 0, 3);
    //     glPopMatrix();
    // }
    // cout << 14 << endl;

    // draw user attacks
    for (const Attack& attack: user.attacks) {
        glPushMatrix();
        glTranslatef(attack.x, attack.y, 0);
        glBindVertexArray(bullet_vao);
        glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
        glDrawArrays(GL_POINTS, 0, 3);
        glPopMatrix();
    }
    
    // glDisableClientState(GL_VERTEX_ARRAY);
    //dislays
    glutSwapBuffers();
}

void input_move(int key_input, int x,  int y) {
    if (key_input == GLUT_KEY_LEFT) {
        // User::input_position = -1;
        user.x -= 0.1;
    }
    else if (key_input == GLUT_KEY_RIGHT) {
        // User::input_position = 1;
        user.x += 0.1;
    }
}

void input_attack(unsigned char key_input, int x, int y) {
    // if user pressed space bar
    if (key_input == 32) {
        user.attacks.push_back(Attack(user.x, user.y + 0.05));
        // cout << User::user_attacks.size() << endl;
    }
}

// void create_enemies(size_t enemy_type){
//     if (enemy_type == 1){
//         Enemies_Type_One* new_enemy = new Enemies_Type_One();
//         enemies.push_back(new_enemy);
//     } else if (enemy_type == 2){
//         Enemies_Type_Two* new_enemy = new Enemies_Type_Two();
//         enemies.push_back(new_enemy);
//     } else if (enemy_type == 3){
//         Enemies_Type_Three* new_enemy = new Enemies_Type_Three();
//         enemies.push_back(new_enemy);
//     } else {
//         cout << "invalid enemy type" << endl;
//     }
// }

// void populating_enemies(size_t type_one, size_t type_two, size_t type_three){
//     for(size_t i = 0; i < type_one; i++){
//         create_enemies(1);
//     }
//     for(size_t i = 0; i < type_two; i++){
//         create_enemies(2);
//     }
//     for(size_t i = 0; i < type_three; i++){
//         create_enemies(3);
//     }
// }   

// void move_enemies(){
//     Enemies* enemy = nullptr;
//     for(size_t i = 0; i < enemies.size(); i++){
//         enemy = enemies.at(i);
//         enemy->enemies_movement();
//     }
// }

// void check_for_collision(){

// }

