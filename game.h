//
// Created by valiant on 31.12.2020.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

typedef struct {
    float hp, x, y;
}Player;

typedef struct {
    bool active;
    float x, y, speed;
}Enemy;

Player player;
Enemy enemy;

void initValues()
{
    player.hp = 100.0f;
    player.y = -0.75f;
    player.x = 0.0f;
    enemy.active = true;
    enemy.speed = (float) (rand() % 3 + 1) / 100.0f;
    enemy.x = (float) (rand() % 640 + 1) / 320.0f - 1;
    enemy.y = 1.2f;
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
    glVertex3f(-1.2f + player.hp / 100.0f, 0.9f, 0.0f);
    glVertex3f(-1.2f + player.hp / 100.0f, 0.8f, 0.0f);
    glVertex3f(-1.2f, 0.8f, 0.0f);
    glEnd();
}

void gameOver()
{
    initValues();
}

void update()
{
    drawPlayer();
    drawEnemy();
    drawHealthBar();
    enemy.y -= enemy.speed;
    if (enemy.y < -1.5f) {
        enemy.speed = (float) (rand() % 3 + 1) / 100.0f;
        enemy.x = (float) (rand() % 640 + 1) / 320.0f - 1;
        enemy.y = 1.2f;
    }
    if (player.y + 0.3f >= enemy.y && player.y <= enemy.y + 0.3f) {
        if (player.x <= enemy.x + 0.2f && player.x >= enemy.x - 0.2f) {
            player.hp--;
        }
    }
    if (player.hp <= 0) {
        gameOver();
    }
}

#endif //SPACEINVADERS_GAME_H