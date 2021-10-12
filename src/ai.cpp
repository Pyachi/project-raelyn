#include "ai.h"
#include <QtMath>
#include "entities.h"
#include "entitytypes.h"
#include "game.h"
#include "utilities.h"

EntityAI<Enemy> AI::enemy1 = [](Enemy* enemy) {
	if (enemy->cycle(50)) {
		Util::bulletCircle(enemy, Bullets::spiralCW, 16, 0);
		Util::bulletCircle(enemy, Bullets::spiralCCW, 16, 0);
	}
	if (enemy->cycle(150, 0))
		enemy->move = QPointF(-200, 200);
	if (enemy->cycle(150, 50))
		enemy->move = QPointF(400, 0);
	if (enemy->cycle(150, 100))
		enemy->move = QPointF(-200, -200);
};

EntityAI<Enemy> AI::enemy2 = [](Enemy* enemy) {
	if (enemy->cycle(80, 0, 8)) {
		Util::bulletCircle(enemy, Bullets::flowerCW, 24, enemy->timeAlive);
		//		Util::bulletCircle(enemy, Bullets::flowerCCW, 8,
		//-enemy->timeAlive);
	}
	if (enemy->cycle(160, 50))
		enemy->move = QPointF(0, 200);
	if (enemy->cycle(160, 130))
		enemy->move = QPointF(0, -200);
};

EntityAI<Bullet> BulletAI::playerBasic = [](Bullet* bullet) {
	bullet->moveBy(0, -40);
};

EntityAI<Bullet> BulletAI::spiralCW = [](Bullet* bullet) {
	bullet->moveFoward(3);
	bullet->setRotation(bullet->rotation() + 0.1);
};

EntityAI<Bullet> BulletAI::spiralCCW = [](Bullet* bullet) {
	bullet->moveFoward(3);
	bullet->setRotation(bullet->rotation() - 0.1);
};

EntityAI<Bullet> BulletAI::flowerCW = [](Bullet* bullet) {
	if (bullet->cycle(10000, 0, 120)) {
		bullet->moveFoward(3);
		bullet->setRotation(bullet->rotation() + 3);
	} else {
		bullet->boundsCheck = true;
		bullet->moveFoward(10);
		bullet->setRotation(bullet->rotation() + 1);
	}
};

EntityAI<Bullet> BulletAI::flowerCCW = [](Bullet* bullet) {
	if (bullet->cycle(10000, 0, 120)) {
		bullet->moveFoward(3);
		bullet->setRotation(bullet->rotation() - 3);
	} else {
		bullet->boundsCheck = true;
		bullet->moveFoward(10);
		bullet->setRotation(bullet->rotation() - 1);
	}
};

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
					player->fireBullet(Bullets::playerBasic, QPointF(0, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBasic, QPointF(10, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBasic, QPointF(-10, 0), 0)
							->setOpacity(0.25);
					break;
			}
		} else {
			switch (player->level) {
				case 1:
					player->fireBullet(Bullets::playerBasic, QPointF(0, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBasic, QPointF(20, 0), 0)
							->setOpacity(0.25);
					player->fireBullet(Bullets::playerBasic, QPointF(-20, 0), 0)
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
