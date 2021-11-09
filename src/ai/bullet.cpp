#include "bullet.h"
#include <QVector2D>
#include <QtMath>
#include "src/entity/entitybullet.h"
#include "src/entity/entityenemy.h"
#include "src/framework/game.h"

namespace Bullets {
AI<EntityBullet> get(BulletAI ai) {
	switch (ai) {
		case AI_PLAYERBASIC:
			return [](EntityBullet* bullet) { bullet->moveBy(0, -40); };

		case AI_PLAYERHOMING:
			return [](EntityBullet* bullet) {
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

		case AI_BASIC8:
			return [](EntityBullet* bullet) { bullet->moveFoward(8); };

		case AI_BASIC10:
			return [](EntityBullet* bullet) { bullet->moveFoward(10); };

		case AI_BASIC12:
			return [](EntityBullet* bullet) { bullet->moveFoward(12); };

		case AI_ACCELERATING:
			return [](EntityBullet* bullet) {
				bullet->moveFoward(pow(bullet->getAge(), 3) / 100000);
			};

		case AI_SCREENWRAPTEST:
			return [](EntityBullet* bullet) {
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

		case AI_FLOWER:
			return [](EntityBullet* bullet) {
				if (bullet->getAge() == 1)
					bullet->borderCheck = false;
				if (bullet->getAge() < 20) {
					bullet->rotate(18);
				} else if (bullet->getAge() == 20)
					bullet->deleteLater();
				bullet->moveFoward(20);
			};
	}
}
}  // namespace Bullets

BulletInfo::BulletInfo(Tex texture,
											 BulletAI ai,
											 double rot,
											 const QPointF& loc,
											 int damage)
		: texture(texture), ai(ai), relRot(rot), relLoc(loc), damage(damage) {}

EntityBullet* BulletInfo::spawn(const Entity* owner,
																double rot,
																const QPointF& loc) const {
	EntityBullet* bullet =
			new EntityBullet(texture, Bullets::get(ai), owner->type, damage);
	bullet->setRotation(owner->rotation() + rot + relRot);
	bullet->setPos(owner->pos() + loc + relLoc);
	return bullet;
}
