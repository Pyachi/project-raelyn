#include "bulletai.h"
#include "src/framework/game.h"
#include "src/entity/bullet.h"
#include "src/entity/enemy.h"
#include <QVector2D>
#include <QtMath>

BulletInfo::BulletInfo(const Texture& texture,
											 const AI<Bullet>& ai,
											 double rot,
											 const QPointF& loc,
											 int damage)
		: texture(texture), ai(ai), relRot(rot), relLoc(loc), damage(damage) {}

Bullet* BulletInfo::spawn(const Entity* owner,
													double rot,
													const QPointF& loc) const {
	Bullet* bullet = new Bullet(this, owner);
	bullet->setRotation(owner->rotation() + rot + relRot);
	bullet->setPos(owner->pos() + loc + relLoc);
	return bullet;
}

namespace BulletType {
const AI<Bullet> PLAYERBASIC = [](Bullet* bullet) { bullet->moveBy(0, -40); };
const AI<Bullet> PLAYERHOMING = [](Bullet* bullet) {
	bullet->rotate(20);
	if (bullet->getNearestEntity(ENEMY) == nullptr) {
		bullet->moveBy(0, -20);
		return;
	}
	QVector2D dir =
			QVector2D(bullet->getNearestEntity(ENEMY)->pos() - bullet->pos());
	dir.normalize();
	dir *= 20;
	bullet->setPos(bullet->pos() + dir.toPointF());
};
const AI<Bullet> BASIC8 = [](Bullet* bullet) { bullet->moveFoward(8); };
const AI<Bullet> BASIC10 = [](Bullet* bullet) { bullet->moveFoward(10); };
const AI<Bullet> BASIC12 = [](Bullet* bullet) { bullet->moveFoward(12); };
const AI<Bullet> ACCELERATING = [](Bullet* bullet) {
	bullet->moveFoward(pow(bullet->getAge(), 3) / 100000);
};
const AI<Bullet> SCREENWRAPTEST = [](Bullet* bullet) {
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
const AI<Bullet> FLOWER = [](Bullet* bullet) {
	if (bullet->getAge() == 1)
		bullet->borderCheck = false;
	if (bullet->getAge() < 20) {
		bullet->rotate(18);
	} else if (bullet->getAge() == 20)
		bullet->deleteLater();
	bullet->moveFoward(20);
};
}
