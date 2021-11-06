#include "bullettype.h"
#include <QVector2D>
#include <QtMath>
#include "src/entity/bullet.h"
#include "src/entity/enemy.h"

BulletInfo::BulletInfo(const Texture& texture,
											 const BulletAI& ai,
											 double relRot,
											 QPointF relPos)
		: texture(texture), ai(ai), relRot(relRot), relPos(relPos) {}

Bullet* BulletInfo::spawn(Entity* owner, const QPointF& loc, double rot) const {
	return new Bullet(this, owner, relPos + loc, relRot + rot);
}

namespace BulletType {
const BulletAI PLAYERBASIC = [](Bullet* bullet) { bullet->moveBy(0, -40); };

const BulletAI PLAYERHOMING = [](Bullet* bullet) {
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

const BulletAI ACCELERATING = [](Bullet* bullet) {
	bullet->moveFoward(pow(bullet->getAge(), 3) / 100000);
};

const BulletAI SCREENWRAPTEST = [](Bullet* bullet) {
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

const BulletAI FLOWER = [](Bullet* bullet) {
	if (bullet->getAge() == 1)
		bullet->borderCheck = false;
	if (bullet->getAge() < 20) {
		bullet->rotate(18);
	} else if (bullet->getAge() == 20)
		bullet->deleteLater();
	bullet->moveFoward(20);
};

const BulletAI BASIC8 = [](Bullet* bullet) { bullet->moveFoward(8); };

const BulletAI BASIC10 = [](Bullet* bullet) { bullet->moveFoward(10); };

const BulletAI BASIC12 = [](Bullet* bullet) { bullet->moveFoward(12); };
}
