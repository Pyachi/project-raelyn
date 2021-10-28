#include "entityinfo.h"
#include <QVector2D>
#include <QtMath>
#include "bullet.h"
#include "enemy.h"
#include "player.h"
#include "texture.h"

PlayerInfo::PlayerInfo(const Texture& texture,
											 const FiringPattern& ai,
											 int normalSpeed,
											 int focusSpeed)
		: texture(texture),
			firingPattern(ai),
			normalSpeed(normalSpeed),
			focusSpeed(focusSpeed) {}

EnemyInfo::EnemyInfo(const Texture& texture, const EnemyAI& ai, int health)
		: texture(texture), ai(ai), health(health) {}

Bullets::BulletInfo(const Texture& texture, const BulletAI& ai)
		: texture(texture), ai(ai) {}

const PlayerInfo PlayerInfo::PYACHI =
		PlayerInfo(Texture::PLAYER1,

const PlayerInfo PlayerInfo:
:AERON =
		PlayerInfo(Texture::PLAYER1,
							 [](Player* player) {
								 switch (player->level) {
									 case 1:
										 if (player->focus) {
											 player->fireBullet(Bullets::PLAYERBASIC,
																					QPointF(-10, 0))->setOpacity(0.25);
											 player->fireBullet(Bullets::PLAYERBASIC,
																					QPointF(0, 0))->setOpacity(0.25);
											 player->fireBullet(Bullets::PLAYERBASIC,
																					QPointF(10, 0))->setOpacity(0.25);
											 if (player->cycle(5)) {
												 player->fireBullet(Bullets::PLAYERHOMING,
																						QPointF(-30, -30))->setOpacity(0.5);
												 player->fireBullet(Bullets::PLAYERHOMING,
																						QPointF(30, -30))->setOpacity(0.5);
											 }
										 } else {
											 player->fireBullet(Bullets::PLAYERBASIC,
																					QPointF(-20, 0))->setOpacity(0.25);
											 player->fireBullet(Bullets::PLAYERBASIC,
																					QPointF(0, 0))->setOpacity(0.25);
											 player->fireBullet(Bullets::PLAYERBASIC,
																					QPointF(20, 0))->setOpacity(0.25);
											 if (player->cycle(5)) {
												 player->fireBullet(Bullets::PLAYERHOMING,
																						QPointF(-50, 0))->setOpacity(0.5);
												 player->fireBullet(Bullets::PLAYERHOMING,
																						QPointF(50, 0))->setOpacity(0.5);
											 }
										 }
										 break;
								 }
							 },
							 18,
							 8);

const EnemyInfo EnemyInfo::ENEMY1 =


const Bullets Bullets::PLAYERBASIC =
		Bullets(Texture::PLAYERBULLETBASIC,
							 [](Bullet* bullet) { bullet->moveBy(0, -40); });

const Bullets Bullets::PLAYERHOMING =
		Bullets(Texture::PLAYERBULLETBASIC, [](Bullet* bullet) {
			bullet->rotate(20);
			if (bullet->getNearestEnemy() == nullptr) {
				bullet->moveBy(0, -20);
				return;
			}
			QVector2D dir =
					QVector2D(bullet->getNearestEnemy()->pos() - bullet->pos());
			dir.normalize();
			dir *= 20;
			bullet->setPos(bullet->pos() + dir.toPointF());
		});

const Bullets Bullets::ACCELERATING =
		Bullets(Texture::BULLETROUND, [](Bullet* bullet) {
			bullet->moveFoward(pow(bullet->timeAlive, 3) / 100000);
		});

const Bullets Bullets::SCREENWRAPTEST =
		Bullets(Texture::BULLETELLIPSE, [](Bullet* bullet) {
			if (bullet->timeAlive == 1)
				bullet->borderCheck = false;
			bullet->moveFoward(5);
			if (bullet->timeAlive > 1 && !bullet->isOnScreen()) {
				bullet->cleanup = true;
				return;
			}
			if (!bullet->isOnScreen()) {
				if (bullet->pos().x() < -340)
					bullet->moveBy(690, 0);
				else if (bullet->pos().x() > 340)
					bullet->moveBy(-690, 0);
				else if (bullet->pos().y() < -340)
					bullet->moveBy(0, 690);
				else if (bullet->pos().y() > 340)
					bullet->moveBy(0, -690);
			}
		});

const Bullets Bullets::FLOWER =
		Bullets(Texture::BULLETELLIPSE, [](Bullet* bullet) {
			if (bullet->timeAlive == 1)
				bullet->borderCheck = false;
			if (bullet->timeAlive < 20) {
				bullet->rotate(18);
			} else if (bullet->timeAlive == 20)
				bullet->cleanup = true;
			bullet->moveFoward(20);
		});
