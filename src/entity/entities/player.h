#ifndef PLAYER_H
#define PLAYER_H

#include <QSet>
#include "src/entity/entity.h"

class Hitbox;

const int baseSpeed = 15;
const int focusSpeed = 5;
const int playerSize = 64;
const int playerHitboxSize = 12;

class Player : public Entity {
public:
    Player(Game*);

    void tick();

private:
    Hitbox* hitbox;
    bool firing = false;
    bool focus = false;
    int level = 1;

    void checkMovement(const QSet<int> &keys);
    void shootBullets();
    void fireBullet(int, int);
};

#endif // PLAYER_H
