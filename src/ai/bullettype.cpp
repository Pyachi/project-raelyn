#include "bullettype.h"
#include <QVector2D>
#include <QtMath>
#include "src/entity/bullet.h"
#include "src/entity/enemy.h"

const BulletAI BulletType::PLAYERBASIC = [](Bullet* bullet) {
	bullet->moveBy(0, -40);
};

const BulletAI BulletType::PLAYERHOMING = [](Bullet* bullet) {
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
};

const BulletAI BulletType::ACCELERATING = [](Bullet* bullet) {
	bullet->moveFoward(pow(bullet->getAge(), 3) / 100000);
};

const BulletAI BulletType::SCREENWRAPTEST = [](Bullet* bullet) {
	if (bullet->getAge() == 1)
		bullet->borderCheck = false;
	bullet->moveFoward(5);
	if (bullet->getAge() > 1 && !bullet->isOnScreen()) {
		bullet->deleteLater();
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
};

const BulletAI BulletType::FLOWER = [](Bullet* bullet) {
	if (bullet->getAge() == 1)
		bullet->borderCheck = false;
	if (bullet->getAge() < 20) {
		bullet->rotate(18);
	} else if (bullet->getAge() == 20)
		bullet->deleteLater();
	bullet->moveFoward(20);
};

const BulletAI BulletType::BASIC8 = [](Bullet* bullet) {
	bullet->moveFoward(8);
};

const BulletAI BulletType::BASIC10 = [](Bullet* bullet) {
	bullet->moveFoward(10);
};

const BulletAI BulletType::BASIC12 = [](Bullet* bullet) {
	bullet->moveFoward(12);
};
