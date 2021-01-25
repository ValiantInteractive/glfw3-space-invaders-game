//
// Created by Uljas Lindell on 25.1.2021.
// Version 0.6

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H
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

bool reloaded;
int score, projectiles, kills;

void drawProjectile();
void updateScore(int);
void killEnemy();
float increaseDifficulty(bool);
bool reload();

Player player;
Enemy enemy;
Projectile bullet[MAX_PROJECTILES];

void initValues() {
    score = 0;
    projectiles = 0;
    kills = 0;
    reloaded = true;
    player.hp = 100.0f;
    player.y = -0.75f;
    player.x = 0.0f;
    enemy.active = true;
    enemy.speed = (float) (rand() % 3 + 1) / 500;
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
    if (reloaded) {
        if (projectiles > 3)
            reloaded = false;
        if (projectiles == MAX_PROJECTILES)
            projectiles = 0;
        bullet[projectiles].active = true;
        bullet[projectiles].x = player.x;
        bullet[projectiles].x = bullet[projectiles].x;
        bullet[projectiles].y = -0.4f;
        projectiles++;
    } else if (!reloaded) {
        reloaded = reload();
    }
}

bool reload() {
    double start, end;
    start = glfwGetTime();
    do
    {
        TODO:
        Some reloading animation os some sort
    }
    while ((end-start) < 3.0);
    return true;
}

void drawProjectile() {
    for (int i = 0; i <= MAX_PROJECTILES; i++) {
        if (bullet[i].active && enemy.active) {
            glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(bullet[i].x - 0.01f, bullet[i].y, 1.0f);
            glVertex3f(bullet[i].x + 0.01f, bullet[i].y, 1.0f);
            glVertex3f(bullet[i].x + 0.01f, bullet[i].y + 0.1f, 1.0f);
            glVertex3f(bullet[i].x - 0.01f, bullet[i].y + 0.1f, 1.0f);
            bullet[i].y += 0.02f;
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
    glVertex3f(-1.2f, 0.9f, 2.0f);
    glVertex3f(-1.2f + player.hp * 2.4f / 100.0f, 0.9f, 2.0f);
    glVertex3f(-1.2f + player.hp * 2.4f / 100.0f, 0.8f, 2.0f);
    glVertex3f(-1.2f, 0.8f, 2.0f);
    glEnd();
}

void gameOver() {
    initValues();
}

void killEnemy() {
    kills++;
    enemy.active = false;
    enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
    enemy.y = 2.0f;
    enemy.speed += increaseDifficulty(false);
}

void updateScore(int amount) {
    score += amount;
    std::cout << "Score: " << score << std::endl;
}

float increaseDifficulty(bool missed) {
    float increase;
    if (!missed) {
        updateScore(50);
        increase = (float) sqrt(kills) / 1000.0f;
    } else {
        updateScore(10);
        increase += 0.001f;
    }
    return increase;
}

void update() {
    drawPlayer();

    if (enemy.active) {
        drawEnemy();
    }

    drawHealthBar();
    drawProjectile();

    enemy.y -= enemy.speed;

    if (!enemy.active) {
        enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
        enemy.y = 2.0f;
        enemy.active = true;
    }
    if (enemy.y > 2.0f) {
        enemy.x = enemy.x = (float) (rand() % 400 + 1) / 200 - 1;
    }
    if (enemy.y < -1.5f) {
        enemy.speed += increaseDifficulty(true);
        enemy.active = false;
    }
    if (player.y + 0.3f >= enemy.y && player.y <= enemy.y + 0.3f) {
        if (player.x <= enemy.x + 0.2f && player.x >= enemy.x - 0.2f) {
            player.hp -= (float) (rand() % 18 + 4);
            enemy.active = false;
        }
    }

    if (player.hp <= 0) {
        gameOver();
    }
}

#endif //SPACEINVADERS_GAME_H
