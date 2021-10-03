#include "enemy.h"
#include "bullet.h"

Enemy::Enemy(Game* game, QString texture, QPoint spawnLoc, int zValue, int health)
    : Hitbox(game, this, texture, spawnLoc, zValue) {
    this->health = health;
    this->dir = QPoint(3,0);
}

void Enemy::tick() {
    time++;
    setPos(pos() + dir);
    if (time % 15 == 0)
        fireBullet(0,0);
    QPointF newPos(pos());
    if (borderCollision(newPos)) dir *= -1;
    foreach(Hitbox* hitbox, collidingHitboxes()) {
        health--;
        hitbox->cleanup = true;
    }
    if (health == 0) cleanup = true;
}

void Enemy::fireBullet(int, int) {
    new Bullet(game, this, "16", getCenter(), QPoint(0,5));
    new Bullet(game, this, "16", getCenter(), QPoint(3,5));
    new Bullet(game, this, "16", getCenter(), QPoint(-3,5));
}
