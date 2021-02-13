// Version 0.5

#ifndef SPACEINVADERS_LOGIC_H
#define SPACEINVADERS_LOGIC_H
#define BORDER 1
#define MAX_PROJECTILES 50
#define MAX_ENEMIES 10

#include "iostream"
#include "cmath"
#include "classes/Enemy.h"

typedef struct {
    float hp, x, y;
} Player;

typedef struct {
    bool active;
    float x, y;
} Projectile;

int score, projectiles, enemies;
const float movementSpeed = 0.01f;

void drawProjectile();

void updateScore(int);

Player player;
Enemy *enemy[MAX_ENEMIES];
Projectile bullet[MAX_PROJECTILES];

void initValues() {
    score = 0;
    projectiles = 0;
    enemies = 0;
    enemy[enemies] = new Enemy;
    player.hp = 100.f;
    player.y = -0.75f;
    player.x = 0.f;
    std::cout << "Score: " << score << std::endl;
    for (auto &i : bullet) {
        i.active = false;
        i.x = player.x;
        i.y = -0.4f;
    }
    while (enemies <= MAX_ENEMIES) {
        enemies++;
        enemy[enemies] = new Enemy;
    }
}

void shoot() {
    if (projectiles == MAX_PROJECTILES)
        projectiles = 0;
    bullet[projectiles].active = true;
    bullet[projectiles].x = player.x;
    bullet[projectiles].x = bullet[projectiles].x;
    bullet[projectiles].y = -0.4f;
    projectiles++;
}

void drawProjectile() {
    for (int i = 0; i <= MAX_PROJECTILES; i++) {
        if (bullet[i].active) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(bullet[i].x - 0.01f, bullet[i].y, 0.0f);
            glVertex3f(bullet[i].x + 0.01f, bullet[i].y, 0.0f);
            glVertex3f(bullet[i].x + 0.01f, bullet[i].y + 0.1f, 0.0f);
            glVertex3f(bullet[i].x - 0.01f, bullet[i].y + 0.1f, 0.0f);
            bullet[i].y += 0.02f;
            for (int j = 0; j <= enemies; j++) {
                if (bullet[i].y >= enemy[j]->y && bullet[i].y <= enemy[j]->y + 0.3f) {
                    if (bullet[i].x <= enemy[j]->x + 0.11f && bullet[i].x >= enemy[j]->x - 0.11f) {
                        bullet[i].active = false;
                        enemy[j]->active = false;
                        updateScore(100);
                    }
                }
            }
            glEnd();
        }
        if (bullet[i].y > 2.0f) {
            bullet[i].active = false;
            bullet[i].x = player.x;
            bullet[i].x = bullet[i].x;
            bullet[i].y = -0.04f;
        }
    }
}

void drawPlayer() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.0f);
    glVertex3f(player.x - 0.1f, player.y, 0.0f);
    glVertex3f(player.x + 0.1f, player.y, 0.0f);
    glVertex3f(player.x + 0.1f, player.y + 0.3f, 0.0f);
    glVertex3f(player.x - 0.1f, player.y + 0.3f, 0.0f);
    glEnd();
}

void drawHealthBar() {
    glBegin(GL_QUADS);
    glColor3f(1.0f - player.hp / 100.0f, player.hp / 100.0f, 0.0f);
    glVertex3f(-1.2f, 0.9f, 1.0f);
    glVertex3f(-1.2f + player.hp * 2.4f / 100.0f, 0.9f, 1.0f);
    glVertex3f(-1.2f + player.hp * 2.4f / 100.0f, 0.8f, 1.0f);
    glVertex3f(-1.2f, 0.8f, 1.0f);
    glEnd();
}

void gameOver() {
    for (auto &i : enemy) {
        delete i;
    }
    initValues();
}

void updateScore(int amount) {
    score += amount;
    std::cout << "Score: " << score << std::endl;
}

void update() {
    drawPlayer();
    drawProjectile();

    for (int i = 0; i <= enemies; i++) {
        if (enemy[i]->active) {
            if (player.y + 0.3f >= enemy[i]->y && player.y <= enemy[i]->y + 0.3f) {
                if (player.x <= enemy[i]->x + 0.2f && player.x >= enemy[i]->x - 0.2f) {
                    player.hp -= (float) (rand() % 18 + 4);
                    enemy[i]->active = false;
                }
            }
        }
        enemy[i]->Update();
    }

    drawHealthBar();

    if (player.hp <= 0) {
        gameOver();
    }
}

#endif //SPACEINVADERS_LOGIC_H