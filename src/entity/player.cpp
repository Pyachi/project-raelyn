#include "player.h"
#include <QtMath>
#include "bullet.h"
#include "enemy.h"
#include "playerhitbox.h"
#include "src/network/connection.h"
#include "src/texture.h"

Players::Players(const Texture& texture,
								 const EntityAI<Player>& firingPattern,
								 int speed,
								 int focusSpeed)
		: texture(texture),
			firingPattern(firingPattern),
			speed(speed),
			focusSpeed(focusSpeed) {}

const Players Players::PYACHI = Players(
		Texture::PLAYER1,
		[](Player* player) {
			switch (player->level) {
				case 1:
					if (player->focus) {
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(-10, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(0, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(10, 0))
								->setOpacity(0.25);
					} else {
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(-20, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(0, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(20, 0))
								->setOpacity(0.25);
					}
					break;
				case 2:
					if (player->focus) {
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(-10, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(0, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(10, 0))
								->setOpacity(0.25);
						if (player->cycle(5)) {
							player->fireBullet(Bullets::PLAYERHOMING, QPointF(-30, -30))
									->setOpacity(0.5);
							player->fireBullet(Bullets::PLAYERHOMING, QPointF(30, -30))
									->setOpacity(0.5);
						}
					} else {
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(-20, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(0, 0))
								->setOpacity(0.25);
						player->fireBullet(Bullets::PLAYERBASIC, QPointF(20, 0))
								->setOpacity(0.25);
						if (player->cycle(5)) {
							player->fireBullet(Bullets::PLAYERHOMING, QPointF(-50, 0))
									->setOpacity(0.5);
							player->fireBullet(Bullets::PLAYERHOMING, QPointF(50, 0))
									->setOpacity(0.5);
						}
					}
					break;
			}
		},
		15,
		5);

Player::Player(const Players& stats, const QPointF& spawn)
		: Entity(stats.texture, spawn),
			firing(false),
			focus(false),
			level(1),
			power(0),
			normalSpeed(stats.speed),
			focusSpeed(stats.focusSpeed),
			firingPattern(stats.firingPattern),
			ai([](Player* player) {
				QSet<int> keys = Game::getKeys();

				player->firing = keys.contains(Qt::Key_Z);
				player->focus = keys.contains(Qt::Key_Shift);

				if (player->focus)
					player->hitbox->setZValue(4);
				else
					player->hitbox->setZValue(-1);

				if (player->firing)
					player->firingPattern(player);

				int dx = 0, dy = 0;
				int speed = player->focus ? player->focusSpeed : player->normalSpeed;
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
				player->setPos(
						player->confineToPlayableArea(player->pos() + QPointF(dx, dy)));

				if (player->power >= 100) {
					player->level++;
					if (player->level == 3)
						player->level = 2;
					player->power = 0;
				}

				if (player->isHit()) {
					player->cleanup = true;
					player->hitbox->cleanup = true;
				}

				Connection::sendPacket("playerLocation",
															 QString::number(player->pos().x()) + ":" +
																	 QString::number(player->pos().y()));
			}),
			hitbox(new PlayerHitbox(this)) {}

bool Player::isHit() {
	if (hitbox->getCollisions<Enemy>().size() > 0)
		return true;
	else
		foreach (Bullet* bullet, hitbox->getCollisions<Bullet>())
			if (dynamic_cast<Enemy*>(bullet->owner))
				return true;
	return false;
}

void Player::tick() {
	timeAlive++;
	ai(this);
}
