// Created by Uljas Lindell on 25.1.2021.
// Version 0.3

#ifndef SPACEINVADERS_LOGIC_H
#define SPACEINVADERS_LOGIC_H
#define BORDER 1
#define MAX_PROJECTILES 50

#include "iostream"
#include "cmath"

typedef struct {
    float hp, x, y;
} Player;

typedef struct {
    bool active;
    float x, y, speed;
} Enemy;

typedef struct {
    bool active;
    float x, y;
} Projectile;

int score, projectiles, kills;

void drawProjectile();

void updateScore(int);

void killEnemy();

void increaseDifficulty(bool);

Player player;
Enemy enemy;
Projectile bullet[MAX_PROJECTILES];

void initValues() {
    score = 0;
    projectiles = 0;
    kills = 0;
    player.hp = 100.0f;
    player.y = -0.75f;
    player.x = 0.0f;
    enemy.active = true;
    enemy.speed = (float) (rand() % 3 + 1) / 5000;
    enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
    enemy.y = 2.5f;
    std::cout << "Score: " << score << std::endl;
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        bullet[i].active = false;
        bullet[i].x = player.x;
        bullet[i].y = -0.4f;
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
        if (bullet[i].active && enemy.active) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(bullet[i].x - 0.01f, bullet[i].y, 0.0f);
            glVertex3f(bullet[i].x + 0.01f, bullet[i].y, 0.0f);
            glVertex3f(bullet[i].x + 0.01f, bullet[i].y + 0.1f, 0.0f);
            glVertex3f(bullet[i].x - 0.01f, bullet[i].y + 0.1f, 0.0f);
            bullet[i].y += 0.002f;
            if (bullet[i].y >= enemy.y && bullet[i].y <= enemy.y + 0.3f) {
                if (bullet[i].x <= enemy.x + 0.11f && bullet[i].x >= enemy.x - 0.11f) {
                    killEnemy();
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

void drawEnemy() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex3f(enemy.x - 0.1f, enemy.y, 0.0f);
    glVertex3f(enemy.x + 0.1f, enemy.y, 0.0f);
    glVertex3f(enemy.x + 0.1f, enemy.y + 0.3f, 0.0f);
    glVertex3f(enemy.x - 0.1f, enemy.y + 0.3f, 0.0f);
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
    initValues();
}

void killEnemy() {
    kills++;
    enemy.active = false;
    enemy.y = 2.0f;
    enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
    increaseDifficulty(false);
}

void updateScore(int amount) {
    score += amount;
    std::cout << "Score: " << score << std::endl;
}

void increaseDifficulty(bool missed) {
    if (!missed) {
        updateScore(100);
        enemy.speed += 0.0001f;
    } else {
        updateScore(50);
        enemy.speed += 0.00005f;
    }
}

void update() {
    drawPlayer();
    drawHealthBar();
    drawProjectile();

    if (enemy.active) {
        drawEnemy();
        enemy.y -= enemy.speed;
    }

    if (player.y + 0.3f >= enemy.y && player.y <= enemy.y + 0.3f) {
        if (player.x <= enemy.x + 0.2f && player.x >= enemy.x - 0.2f) {
            player.hp -= (float) (rand() % 18 + 4);
            enemy.active = false;
        }
    }
    if (!enemy.active) {
        enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
        enemy.y = 2.0f;
        enemy.active = true;
    }
    if (enemy.y > 2.0f) {
        enemy.x = enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
    }
    if (enemy.y < -1.5f) {
        enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
        enemy.y = 2.0f;
        enemy.active = true;
        increaseDifficulty(true);
    }

    if (player.hp <= 0) {
        gameOver();
    }
}

#endif //SPACEINVADERS_LOGIC_H