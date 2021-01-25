//
// Created by valiant on 31.12.2020.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H
#include "iostream"
#include "cmath"

typedef struct {
    float hp, x, y;
}Player;

typedef struct {
    bool active;
    float x, y, speed;
}Enemy;

int score;

Player player;
Enemy enemy;

void initValues()
{
    score = 0;
    player.hp = 100.0f;
    player.y = -0.75f;
    player.x = 0.0f;
    enemy.active = true;
    enemy.speed = (float) (rand() % 3 + 1) / 100.0f;
    enemy.x = (float) (rand() % 640 + 1) / 320.0f - 1;
    enemy.y = 2.5f;
    std::cout << "Score: " << score << std::endl;
}

void drawPlayer()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.0f);
    glVertex3f(player.x-0.1f, player.y, 0.0f);
    glVertex3f(player.x+0.1f, player.y, 0.0f);
    glVertex3f(player.x+0.1f, player.y+0.3f, 0.0f);
    glVertex3f(player.x-0.1f, player.y+0.3f, 0.0f);
    glEnd();
}

void drawEnemy()
{
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.0f, 0.0f);
    glVertex3f(enemy.x - 0.1f, enemy.y, 0.0f);
    glVertex3f(enemy.x + 0.1f, enemy.y, 0.0f);
    glVertex3f(enemy.x + 0.1f, enemy.y + 0.3f, 0.0f);
    glVertex3f(enemy.x - 0.1f, enemy.y + 0.3f, 0.0f);
    glEnd();
}

void drawHealthBar()
{
    glBegin(GL_QUADS);
    glColor3f(1.0f - player.hp / 100.0f, player.hp / 100.0f, 0.0f);
    glVertex3f(-1.2f, 0.9f, 0.0f);
    glVertex3f(-1.2f + player.hp * 2.4f / 100.0f, 0.9f, 0.0f);
    glVertex3f(-1.2f + player.hp * 2.4f / 100.0f, 0.8f, 0.0f);
    glVertex3f(-1.2f, 0.8f, 0.0f);
    glEnd();
}

void gameOver()
{
    initValues();
}

void updateScore(int amount)
{
    score += amount;
    std::cout << "Score: " << score << std::endl;
    if(score % 10 == 0) {
        enemy.speed += (float) sqrt(score) / 1000.0f;
    }
}

void update()
{
    drawPlayer();
    drawEnemy();
    drawHealthBar();
    enemy.y -= enemy.speed;
    if(enemy.y > 2.0f)
    {
        enemy.x = (float) (rand() % 720 + 1) / 320.0f - 1;
    }
    if(!enemy.active){
        enemy.x = (float) (rand() % 720 + 1) / 320.0f - 1;
        enemy.y = 2.0f;
        enemy.active = true;
    }
    if (enemy.y < -1.5f) {
        updateScore(1);
        enemy.x = (float) (rand() % 720 + 1) / 320.0f - 1;
        enemy.y = 2.0f;
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