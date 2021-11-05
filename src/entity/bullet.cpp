#include "bullet.h"
#include "assets.h"
#include "src/ai/bulletinfo.h"

Bullet::Bullet(const BulletInfo* info,
							 Entity* owner,
							 const QPointF& spawn,
							 double rotation)
		: Entity(info->texture, spawn),
			owner(owner),
			borderCheck(true),
			ai(info->ai) {
	setRotation(rotation);
	Game::addEntity(this);
}

void Bullet::tick() {
	age++;
	ai(this);
	if (borderCheck && !isOnScreen())
		deleteLater();
}
