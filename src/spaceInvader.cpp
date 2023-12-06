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
void update(int);
void manage_attack(int);
// void populating_enemies(size_t type_one, size_t type_two, size_t type_three);
// void create_enemies(size_t enemy_type);
void init_buffers();
void move_enemies();
void start_screen();
void end_lost_screen();
void end_win_screen();

// void check_for_collision()

GLuint ship_vao;
GLuint ship_vbo;
// GLuint enemies_vao;
// GLuint enemies_vbo;
GLuint bullet_vao;
GLuint bullet_vbo;
User user;
bool is_start = true;
bool is_attack = true;
bool is_playing = true;
// vector <Enemies*> enemies; 

int main(int argc, char**argv){
    // populating_enemies(1,1,1);    
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "error" << endl;
    //     }
    // else {
    //     cout << "no_error" << endl;
    // }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "no error" << endl;
    //     }
    // else {
    //     cout << "error" << endl;
    // }
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glutInitWindowSize(500, 700);

    glutCreateWindow("window");
    glClearColor(0.05f, 0.0f, 0.1f, 1.0f);

    // User user_;
    cout << 1 << endl;
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "no error" << endl;
    //     }
    // else {
    //     cout << "error" << endl;
    // }
    cout << 2 << endl;


    // sleep(1);
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "no error" << endl;
    //     }
    // else {
    //     cout << "error" << endl;
    // }

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
    cout << 7 << endl;
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
    // GLenum error = glGetError();
    //     if (error != GL_NO_ERROR) {
    //        cout << "1error" << endl;
    //     }
    //     else {
    //        cout << "1no error" << endl;
    //     }
    // // GLenum error = glGetError();
    // // if (error != GL_NO_ERROR) {
    // //     cout << "no error" << endl;
    // //     }
    // // else {
    // //     cout << "error" << endl;
    // // }
    // GLfloat button[12] = {
    //     0.2f, 0.2f,
    //     0.2f, -0.2f,
    //     -0.2f, 0.2f,

    //     -0.2f, 0.2f,
    //     -0.2f, -0.2f,
    //     0.2f, -0.2f,
    // };
    // // glColor3f(1.0f,0.0f,0.0f); // Red color 
    // // glRectf(-0.20f, 0.20f, 0.20f, -0.20f);
    // GLuint start_vao = 1;
    // GLuint start_vbo = 1;
    // // GLuint spaceship_color_vbo;
    // error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "2.5error" << endl;
    //     }
    // else {
    //     cout << "2.5no error" << endl;
    // }
    // // glBindVertexArray(start_vao);
    // error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "2.10error" << endl;
    //     }
    // else {
    //     cout << "2.10no error" << endl;
    // }

    // glGenBuffers(1, &start_vao);
    // glBindBuffer(GL_ARRAY_BUFFER, start_vao);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(button), button, GL_DYNAMIC_DRAW);
    // glVertexPointer(2, GL_FLOAT, 0, nullptr);
    // error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "2error" << endl;
    //     }
    // else {
    //     cout << "2no error" << endl;
    // }

    // glGenBuffers(1, &start_vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, start_vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(button), button, GL_DYNAMIC_DRAW);
    // glEnableVertexAttribArray(0);
    // error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "2error" << endl;
    //     }
    // else {
    //     cout << "2no error" << endl;
    // }
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
    // error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "error" << endl;
    //     }
    // else {
    //     cout << "no error" << endl;
    // }
    // glColor3f(1.0f, 0.0f, 0.0f);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // glutSwapBuffers();
    // //cleaning
    // // glDisableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    // // cout << glGetError() << endl;
    // error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "error" << endl;
    //     }
    // else {
    //     cout << "no error" << endl;
    // }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRasterPos2i(-1.0, 0.02);
    glColor3f(-0.20f, 1.0f, 1.0f);
    const unsigned char* start_string_literal = reinterpret_cast<const unsigned char*>("_____________________Click to start_______________________________________");
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, start_string_literal);

    // glColor3f(-.20f, 1.0f, 0.0f);
    // glRectf(-0.75f,-0.75f, -0.65f, -0.70f);

    // if (error != GL_NO_ERROR) {
    //     cout << "2error" << endl;
    //     }
    // else {
    //     cout << "2no error" << endl;
    // }
    // // glutSwapBuffers();
    
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

    cout << "here" << endl;
    glutPostRedisplay();
    if (!user.attacks.empty()) {
        if (user.attacks.at(0).y >= 2.00) {
            user.attacks.erase(user.attacks.begin());
        }
    }
    for (Attack& attack: user.attacks) {
        attack.y += 0.01;
    }
    // is_attack = true;

    // create attack ball if user_input == space
    glutTimerFunc(33, update, 0);
}

void manage_attack(int) {
    is_attack = true;
    if (is_playing) {
        score += 1;
    }
    glutTimerFunc(300, manage_attack, 0);
}

void display(){
    cout << 1 << endl;
    if (is_start && is_playing) {
        start_screen();
    }
    else if (score < 0) {
        end_lost_screen();
    }
    else if (score > 30) {
        end_win_screen();
    }
    else {
    
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "no error" << endl;
    // }
    // else {
    //     cout << "error" << endl;
    // }
    // cout << 11 << endl;
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "no error" << endl;
    //     }
    // else {
    //     cout << "error" << endl;
    // }
        glLoadIdentity();
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "no error" << endl;
    //     }
    // else {
    //     cout << "error" << endl;
    // }
    // cout << 12 << endl;
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glRasterPos2f(0.650f, 0.90f);
        glColor3f(-0.20f, 1.0f, 1.0f);
        string score_string = to_string(score);
        score_string = "score: " + score_string;
        const char* score_literal = score_string.c_str();
        const unsigned char* score_string_literal = reinterpret_cast<const unsigned char*>(score_literal);

        glutBitmapString(GLUT_BITMAP_HELVETICA_18, score_string_literal);

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
        glColor3f(1.0f, 0.0f, 0.0f);
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
            glColor3f(0.0f, 1.0f, 1.0f);
            glDrawArrays(GL_POINTS, 0, 3);
            glPopMatrix();
        }
    
    // glDisableClientState(GL_VERTEX_ARRAY);
        cout << "dislays" << endl;
    }
    glutSwapBuffers();
    // GLenum error = glGetError();
    // if (error != GL_NO_ERROR) {
    //     cout << "error" << endl;
    // }
    // else {
    //     cout << "no error" << endl;
    // }
}

void input_move(int key_input, int x,  int y) {
    // if (is_start) {
    //     return;
    // }
    cout << "here in_move" << endl;
    if (key_input == GLUT_KEY_LEFT) {
        // User::input_position = -1;
        user.x -= 0.1;
        // glutPostRedisplay();
    }
    else if (key_input == GLUT_KEY_RIGHT) {
        // User::input_position = 1;
        user.x += 0.1;
        // glutPostRedisplay();

    }
}

// start button click checker
void input_mouse(int click, int state, int x, int y) {
    // if (!is_start) {
    //     return;
    // }
    if ((click  == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        double x_calc = (2.0 * x) / 500.0 - 1.0;
        double y_calc = 1.0 - (2.0 * y) / 700.0;
        if ((x_calc < 0.2) && (x_calc > -0.2) && (y_calc < 0.2) && (y_calc > -0.2)) {
            cout << "works" << endl;
            is_start = false;
            score = 0;
            is_playing = true;
            init_buffers();
            glutPostRedisplay();
        }
    }
}

void input_attack(unsigned char key_input, int x, int y) {
    // if (is_start) {
    //     return;
    // }
    // if user pressed space bar
    if ((key_input == 32) & is_attack) {
        user.attacks.push_back(Attack(user.x, user.y + 0.05));
        // score = -1;
        glutPostRedisplay();
        is_attack = false;

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

