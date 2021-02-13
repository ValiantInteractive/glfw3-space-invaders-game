#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H


class Enemy {
private:
    float speed;

    void Respawn();

    void Draw();

public:
    bool active;
    float x, y;

    void Update();

    Enemy();

    ~Enemy();
};

#endif //SPACEINVADERS_ENEMY_H
