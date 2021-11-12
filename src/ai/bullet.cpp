#include "bullet.h"
#include "Entity"
#include "AI"

namespace Bullets {
AI<EntityBullet> get(BulletAI ai) {
	switch (ai) {
		case AI_PLAYERBASIC:
			return [](EntityBullet* bullet) { bullet->moveForward(40); };

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

		case AI_BASIC1:
			return [](EntityBullet* bullet) { bullet->moveForward(1); };

		case AI_BASIC2:
      return [](EntityBullet* bullet) { bullet->moveForward(2); };

		case AI_BASIC3:
			return [](EntityBullet* bullet) { bullet->moveForward(3); };

		case AI_BASIC4:
      return [](EntityBullet* bullet) { bullet->moveForward(4); };

		case AI_BASIC5:
			return [](EntityBullet* bullet) { bullet->moveForward(5); };

		case AI_BASIC6:
      return [](EntityBullet* bullet) { bullet->moveForward(6); };

		case AI_BASIC7:
			return [](EntityBullet* bullet) { bullet->moveForward(7); };

		case AI_BASIC8:
      return [](EntityBullet* bullet) { bullet->moveForward(8); };

		case AI_BASIC9:
			return [](EntityBullet* bullet) { bullet->moveForward(9); };

		case AI_BASIC10:
      return [](EntityBullet* bullet) { bullet->moveForward(10); };

		case AI_BASIC11:
			return [](EntityBullet* bullet) { bullet->moveForward(11); };

		case AI_BASIC12:
      return [](EntityBullet* bullet) { bullet->moveForward(12); };

		case AI_ACCELERATING:
      return [](EntityBullet* bullet) {
        bullet->moveForward(pow(bullet->getAge(), 3) / 100000);
      };

		case AI_SCREENWRAPTEST:
      return [](EntityBullet* bullet) {
        if (bullet->getAge() == 1)
          bullet->borderCheck = false;
        bullet->moveForward(5);
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
        bullet->moveForward(20);
      };
  }
}
EntityBullet* spawn(BulletAI ai,
										BulletInfo info,
										Texture texture,
										const Entity* owner,
										double rot,
										const QPointF& loc,
										int scale,
										int damage) {
	EntityBullet* bullet = new EntityBullet(texture, get(ai), owner);
	bullet->setRotation(bullet->rotation() + info.rot + rot);
	bullet->setPos(bullet->pos() + info.loc + loc);
	bullet->setScale(info.scale * scale);
	bullet->damage = damage;
	return bullet;
}
}  // namespace Bullets
