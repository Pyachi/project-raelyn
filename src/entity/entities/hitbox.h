#ifndef COLLIDER_H
#define COLLIDER_H

#include "src/entity/entity.h"
#include <QList>

class Hitbox : public Entity {
public:
    Hitbox(Game*,
           Entity* owner,
           QString texture,
           QPoint spawnLoc,
           int zValue);

    virtual void tick() {}

    QList<Hitbox*> collidingHitboxes();

protected:
    Entity* owner;
};

#endif // COLLIDER_H
