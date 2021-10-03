#include "bullet.h"
#include "src/game/game.h"
#include "hitbox.h"

Bullet::Bullet(Game* game, Entity* owner, QString texture, QPoint spawnLoc, QPoint dir)
    : Hitbox(game, owner, texture, spawnLoc, 1) {
    this->dir = dir;
}

void Bullet::tick() {
    setPos(pos() + dir);
    QPointF newPos(pos());
    if (borderCollision(newPos))
        cleanup = true;
}
