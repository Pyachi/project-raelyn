#ifndef BULLET_H
#define BULLET_H

#include "entityinfo.h"

class Bullet : public AIEntity<Bullet>,
							 public LinkedEntity,
							 public CollidableEntity {
 public:
	Bullet(Game*, const BulletInfo&, BaseEntity*, const QPointF&, double);

	bool borderCheck;

	void tick() override;
};

#endif  // BULLET_H
