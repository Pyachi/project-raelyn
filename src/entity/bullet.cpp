#include "bullet.h"
#include "src/game.h"
#include "src/ai/bulletai.h"

Bullet::Bullet(const BulletInfo* info, const Entity* owner)
		: Entity(BULLET, info->texture),
			ownerType(owner->type),
			borderCheck(true),
			damage(info->damage),
			ai(info->ai) {
	Game::addEntity(this);
}

void Bullet::tick() {
	age++;
	ai(this);
	if (borderCheck && !isOnScreen())
		deleteLater();
}
