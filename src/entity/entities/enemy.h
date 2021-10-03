#ifndef ENEMY_H
#define ENEMY_H

#include "hitbox.h"

class Enemy : public Hitbox {
public:
    Enemy(Game*,
          QString texture,
          QPoint spawnLoc,
          int zValue,
          int health);

    void tick();

private:
    QPoint dir;
    int time;
    int health;

    void fireBullet(int, int);
};

#endif // ENEMY_H
