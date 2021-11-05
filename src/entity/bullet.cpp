#include "bullet.h"
#include "assets.h"
#include "src/ai/bulletinfo.h"

Bullet::Bullet(const BulletInfo* info,
							 Entity* owner,
							 const QPointF& spawn,
							 double rotation)
		: Entity(info->texture, spawn),
			borderCheck(true),
			owner(owner),
			ai(info->ai) {
	setRotation(rotation);
	Game::addEntity(this);
}

Entity* Bullet::getOwner() const { return owner; }

void Bullet::tick() {
	age++;
	ai(this);
	if (borderCheck && !isOnScreen())
		deleteLater();
}
