#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
// #include <GL/glu.h>
#include <GL/freeglut.h>
#include "user.h"
#include <cstdlib>
#include <unistd.h>
#include <vector>

using namespace std;

void display();
void input_move(int key_input, int x, int y);
void input_attack(unsigned char key_input, int x, int y);
void update(int);

void init_buffers();

GLuint ship_vao;
GLuint ship_vbo;
GLuint bullet_vao;
GLuint bullet_vbo;
User user;

int main(int argc, char**argv){

    glutInit(&argc, argv);
    glutInitContextVersion(2, 0);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize(500, 700);

    glutCreateWindow("window");
    glClearColor(0.05f, 0.0f, 0.1f, 1.0f);

    // User user_;
    init_buffers();

    glutDisplayFunc(display);
    // sleep(1);
    glutKeyboardFunc(input_attack);
    glutSpecialFunc(input_move);

    glutTimerFunc(33, update, 0);

    glutMainLoop();
    return 0;
}

void init_buffers() {
    GLfloat spaceship[6] = {
        +0.05f, -0.05f,
        -0.05f, -0.05f,
         0.00f, +0.05f
    };

    GLfloat bullet[6] = {
        +0.005f, -0.005f,
        -0.005f, -0.005f,
         0.000f, +0.005f
    };

    std::cout << glGetString(GL_VERSION) << '\n';;

    glEnableClientState(GL_VERTEX_ARRAY);

    GLuint ids[2] = {42, 42};
    glGenVertexArrays(2, ids);
    ship_vao   = ids[0];
    bullet_vao = ids[1];


    // glGenVertexArrays(1, &ship_vao);
    glBindVertexArray(ship_vao);

    glGenBuffers(1, &ship_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spaceship), spaceship, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);


    // glGenVertexArrays(1, &bullet_vao);
    glBindVertexArray(bullet_vao);

    glGenBuffers(1, &bullet_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bullet), bullet, GL_DYNAMIC_DRAW);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glBindVertexArray(0);

    std::cout << "Ship:   " << ship_vao   << ' ' << ship_vbo   << '\n';
    std::cout << "Bullet: " << bullet_vao << ' ' << bullet_vbo << '\n';
};

void update(int) {
    // move things
    glutPostRedisplay();
    // if ((User::input_position == 1) && (User::user_spaceship[0] < 1)) {
    //     for (GLuint i = 0; i < 3; ++i) {
    //         User::user_spaceship[i * 2] += 0.02;
    //     }
    // }
    // else if ((User::input_position == -1) && (User::user_spaceship[2] > -1)) {
    //     for (GLuint i = 0; i < 3; ++i) {
    //             User::user_spaceship[i * 2] -= 0.02;
    //     }
    // }
    // User::input_position = 0;

    // // modify the position of the attack balls 
    // // delete it when it reaches the end 
    // // GLfloat* one_attack = nullptr;
    // if (!User::user_attacks.empty()) {
    //     if (User::user_attacks.at(0)[5] > 0.98f) {
    //         User::user_attacks.erase(User::user_attacks.begin());
    //     }
    // }

    // // move the attack ball by 0.01
    // // one_attack = nullptr;
    // if (!User::user_attacks.empty()) {
    //     for (size_t i = 0; i < User::user_attacks.size(); ++i) {
    //         // cout << "attack i: " << i << endl;
    //         for (size_t j = 0; j < 3; ++j) {
    //             User::user_attacks.at(i)[j * 2 + 1] += 0.01f;  
    //         }
    //     }
    // }

    for (Attack& attack: user.attacks) {
        attack.y += 0.01;
    }


    // create attack ball if user_input == space
    glutTimerFunc(33, update, 0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //draw userspaceship  

    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, (User::user_attacks.size() + 1) * sizeof(User::user_spaceship), User::user_spaceship, GL_DYNAMIC_DRAW);
    // glEnableClientState(GL_VERTEX_ARRAY);
    // glVertexPointer(2, GL_FLOAT, 0, nullptr);
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    glPushMatrix();
    glTranslatef(user.x, user.y, 0);
    glBindVertexArray(ship_vao);
    glBindBuffer(GL_ARRAY_BUFFER, ship_vbo);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();

    // finished drawing spaceship

    // draw user attacks
    for (const Attack& attack: user.attacks) {
        // GLuint vao_;
        // glGenVertexArrays(1, &vao_);
        // glBindVertexArray(vao_);

        // GLuint vbo_;
        // glGenBuffers(1, &vbo_);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        // glBufferData(GL_ARRAY_BUFFER, (User::user_attacks.size() + 1) * sizeof(User::user_spaceship), User::user_attacks.at(i), GL_DYNAMIC_DRAW);
        // glEnableClientState(GL_VERTEX_ARRAY);
        // glVertexPointer(2, GL_FLOAT, 0, nullptr);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        glPushMatrix();
        glTranslatef(attack.x, attack.y, 0);
        glBindVertexArray(bullet_vao);
        glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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
        // GLfloat new_attack[6];
        // // cout << "here" << endl;

        // // making new attack ball
        // new_attack[0] = (User::user_spaceship[0] + User::user_spaceship[4]) / 2.0f;
        // new_attack[1] = User::user_spaceship[5] + 0.01f;
        // new_attack[2] = (User::user_spaceship[2] + User::user_spaceship[4]) / 2.0f;
        // new_attack[3] = User::user_spaceship[5] + 0.01f;
        // new_attack[4] = (new_attack[0] + new_attack[2]) / 2.0f;
        // new_attack[5] = new_attack[1] + 0.04f;
        // User::user_attacks.push_back(new_attack);

        user.attacks.push_back(Attack(user.x, user.y + 0.05));
        // cout << User::user_attacks.size() << endl;
    }
}
