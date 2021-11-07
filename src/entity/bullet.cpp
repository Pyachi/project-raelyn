#include "bullet.h"
#include "src/ai/bulletai.h"

Bullet::Bullet(const BulletInfo* info, const Entity* owner)
		: Entity(BULLET, info->texture),
			ownerType(owner->type),
			borderCheck(true),
			ai(info->ai) {}

void Bullet::tick() {
	age++;
	ai(this);
	if (borderCheck && !isOnScreen())
		deleteLater();
}
