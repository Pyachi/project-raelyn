#include "bullet.h"

Bullet::Bullet(Game* game,
							 const BulletInfo& info,
							 BaseEntity* owner,
							 const QPointF& spawn,
							 double rotation)
		: AIEntity<Bullet>(game, info.texture, info.ai, spawn),
			LinkedEntity(owner),
			CollidableEntity(),
			borderCheck(true) {
	setRotation(rotation);
}

void Bullet::tick() {
	timeAlive++;
	ai(this);
	if (borderCheck && !isOnScreen())
		cleanup = true;
}
