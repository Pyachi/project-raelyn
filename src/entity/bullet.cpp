#include "bullet.h"
#include <QVector2D>
#include <QtMath>
#include "enemy.h"

Bullets::Bullets(const Texture& texture, const BulletAI& ai)
		: texture(texture), ai(ai) {}

const Bullets Bullets::PLAYERBASIC =
		Bullets(Texture::PLAYERBULLETBASIC,
						[](Bullet* bullet) { bullet->moveBy(0, -40); });

const Bullets Bullets::PLAYERHOMING =
		Bullets(Texture::PLAYERBULLETBASIC, [](Bullet* bullet) {
			bullet->rotate(20);
			if (bullet->getNearestEntity<Enemy>() == nullptr) {
				bullet->moveBy(0, -20);
				return;
			}
			QVector2D dir =
					QVector2D(bullet->getNearestEntity<Enemy>()->pos() - bullet->pos());
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

const Bullets Bullets::BASIC8 =
		Bullets(Texture::BULLETROUND,
						[](Bullet* bullet) { bullet->moveFoward(8); });

const Bullets Bullets::BASIC10 =
		Bullets(Texture::BULLETROUND,
						[](Bullet* bullet) { bullet->moveFoward(10); });

const Bullets Bullets::BASIC12 =
		Bullets(Texture::BULLETROUND,
						[](Bullet* bullet) { bullet->moveFoward(12); });

Bullet::Bullet(const Bullets& info,
							 BaseEntity* owner,
							 const QPointF& spawn,
							 double rotation)
		: BaseEntity(info.texture, spawn),
			borderCheck(true),
			owner(owner),
			ai(info.ai) {
	setRotation(rotation);
}

void Bullet::tick() {
	timeAlive++;
	ai(this);
	if (borderCheck && !isOnScreen())
		cleanup = true;
}
