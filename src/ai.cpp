#include "ai.h"
#include <QtMath>
#include "entities.h"
#include "entitytypes.h"
#include "game.h"
#include "utilities.h"

EntityAI<PlayerHitbox> AI::playerHitbox = [](PlayerHitbox* hitbox) {
	hitbox->setCenter(hitbox->owner->getCenter());
};

EntityAI<Player> AI::player1 = [](Player* player) {
	QSet<int> keys = player->game->getKeys();

	player->firing = keys.contains(Qt::Key_Z);
	player->focus = keys.contains(Qt::Key_Shift);

	player->hitbox->setVisible(player->focus);

	if (player->firing) {
		if (player->focus) {
			switch (player->level) {
				case 1:
					player->fireBullet(Bullets::playerBullet1, QPointF(0, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBullet1, QPointF(10, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBullet1, QPointF(-10, 0), 0)
							->setOpacity(0.25);
					break;
			}
		} else {
			switch (player->level) {
				case 1:
					player->fireBullet(Bullets::playerBullet1, QPointF(0, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBullet1, QPointF(20, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBullet1, QPointF(-20, 0), 0)
							->setOpacity(0.25);
					break;
			}
		}
	}

	int dx = 0, dy = 0;
	int speed = player->focus ? 5 : 15;
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
	QPointF newPos(player->pos() + QPointF(dx, dy));
	Util::confineToPlayableArea(newPos, player->pixmap().size());
	player->setPos(newPos);

	if (player->isHit()) {
		player->cleanup = true;
		player->hitbox->cleanup = true;
	}
};

EntityAI<Enemy> AI::enemy1 = [](Enemy* enemy) {
	if (enemy->timeAlive % 10 == 0) {
		Util::bulletCircle(enemy, Bullets::enemyBullet2, 8, enemy->timeAlive);
	}
};

EntityAI<Bullet> AI::playerBullet1 = [](Bullet* bullet) {
	bullet->moveBy(0, -40);
};

EntityAI<Bullet> AI::enemyBullet1 = [](Bullet* bullet) {
	if (bullet->timeAlive < 120) {
		bullet->moveFoward(5);
		bullet->setRotation(bullet->rotation() + 3);
	} else if (bullet->timeAlive < 2000) {
		bullet->moveFoward(10);
		bullet->setRotation(bullet->rotation() + 1);
	} else
		bullet->cleanup = true;
	if (bullet->timeAlive == 120)
		bullet->boundsCheck = true;
};
