#include "Enemy.h"
#include "GL/gl.h"
#include "cmath"

Enemy::Enemy() {
    active = false;
}

Enemy::~Enemy() {

}

void Enemy::Respawn() {
    x = (float) (rand() % 400 + 1) / 200.f - 1.f;
    y = 2.5f;
    speed = (float) (rand() % 10 + 3) / 600.f;
    active = true;
}

void Enemy::Draw() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex3f(x - 0.1f, y, 0.0f);
    glVertex3f(x + 0.1f, y, 0.0f);
    glVertex3f(x + 0.1f, y + 0.3f, 0.0f);
    glVertex3f(x - 0.1f, y + 0.3f, 0.0f);
    glEnd();
}

void Enemy::Update() {
    if (active) {
        if (y > 2.0f) {
            x = x = (float) (rand() % 400 + 1) / 200 - 1;
        }
        if (y < -1.5f) {
            active = false;
        }
        Draw();
        y -= speed;
    } else {
        Respawn();
    }
}