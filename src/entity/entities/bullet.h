#ifndef BULLET_H
#define BULLET_H

#include "hitbox.h"

class Bullet : public Hitbox {
public:
    Bullet(Game*,
           Entity* owner,
           QString texture,
           QPoint spawnLoc,
           QPoint dir);

    void tick();

private:
    QPoint dir;
};

#endif // BULLET_H
