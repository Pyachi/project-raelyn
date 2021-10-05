#include "player.h"
#include <QtMath>
#include "playerhitbox.h"
#include "src/assets/textures.h"
#include "src/entity/ai/ai.h"
#include "src/game/game.h"

Player::Player(Game* game)
		: BaseEntity(game, Textures::player, QPoint(400, 400)) {
	hitbox = new PlayerHitbox(game, Textures::playerHitbox, this);
	hitbox->setVisible(false);
}

void Player::tick() {
	BaseEntity::tick();
	checkMovement(game->getKeys());

	firing = game->getKeys().contains(Qt::Key_Z);
	focus = game->getKeys().contains(Qt::Key_Shift);

	if (focus)
		hitbox->setVisible(true);
	else
		hitbox->setVisible(false);

	if (firing)
		shootBullets();

	if (!getValidHits().isEmpty()) {
		hitbox->cleanup = true;
		cleanup = true;
	}
}

void Player::checkMovement(const QSet<int>& keys) {
	int dx = 0, dy = 0;
	int speed = focus ? 5 : 15;
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
		switch (level) {
			case 1:
				fireBullet(10, 0);
				fireBullet(0, 0);
				fireBullet(-10, 0);
				break;
			case 2:

				break;
		}
	} else {
		switch (level) {
			case 1:
				fireBullet(20, 0);
				fireBullet(0, 0);
				fireBullet(-20, 0);
				break;
			case 2:

				break;
		}
	}
}

void Player::fireBullet(int dx, int dy) {
	BaseEntity::fireBullet(Textures::playerBullet, getCenter() + QPoint(dx, dy),
												 AI::playerBullet, 0)
			->setOpacity(0.25);
}

QList<CollidableEntity*> Player::getValidHits() {
	QList<CollidableEntity*> list;
	foreach (CollidableEntity* entity, hitbox->getCollidingEntities()) {
		if (dynamic_cast<Enemy*>(entity))
			list.append(entity);
		else if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Enemy*>(bullet->getOwner()))
				list.append(entity);
	}
	return list;
}
