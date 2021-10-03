#include "player.h"
#include "src/game/game.h"
#include "bullet.h"
#include "hitbox.h"
#include <QtMath>
#include <QDebug>

Player::Player(Game* game) : Entity(game, ":/images/player.png", QPoint(400, 400), 2) {
		hitbox = new Hitbox(game, this, ":/images/player_hitbox.png", getCenter(), 3);
}

void Player::tick() {
    checkMovement(game->getKeys());

    firing = game->getKeys().contains(Qt::Key_Z);
    focus = game->getKeys().contains(Qt::Key_Shift);

    if (focus) hitbox->setVisible(true);
    else hitbox->setVisible(false);
    hitbox->setCenter(getCenter());

    if (firing) shootBullets();

//    qDebug() << hitbox->collidingHitboxes().size();

    if (!hitbox->collidingHitboxes().isEmpty()) {
        hitbox->cleanup = true;
        cleanup = true;
    }
}

void Player::checkMovement(const QSet<int> &keys) {
    int dx = 0, dy = 0;
    int speed = focus ? focusSpeed : baseSpeed;
    if (keys.contains(Qt::Key_Right))
        dx += speed;
    if (keys.contains(Qt::Key_Left))
        dx -= speed;
    if (keys.contains(Qt::Key_Down))
        dy += speed;
    if (keys.contains(Qt::Key_Up))
        dy -= speed;
    if (dx != 0 && dy != 0) {
        dx /= sqrt(2);
        dy /= sqrt(2);
    }
    QPointF newPos(x() + dx, y() + dy);
    borderCollision(newPos);
    setPos(newPos);
}

void Player::shootBullets() {
    if (focus) {
        switch(level) {
        case 1:
            fireBullet(10,0);
            fireBullet(0,0);
            fireBullet(-10,0);
            break;
        case 2:


            break;
        }
    } else {
        switch(level) {
        case 1:
            fireBullet(20,0);
            fireBullet(0,0);
            fireBullet(-20,0);
            break;
        case 2:

            break;
        }
    }
}

void Player::fireBullet(int dx, int dy) {
		Bullet* bullet = new Bullet(game, this, ":/images/player_bullet.png", getCenter() + QPoint(dx, dy), QPoint(0,-40));
    bullet->setOpacity(0.25);
}
