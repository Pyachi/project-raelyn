#include "entitybullet.h"
#include "Framework"

EntityBullet::EntityBullet(Texture tex,
													 AI<EntityBullet> ai,
													 const Entity* owner)
		: Entity(BULLET, tex),
			ownerType(owner->type),
			borderCheck(true),
			damage(1),
			ai(ai) {
	Game::addEntity(this);
	rotate(owner->rotation());
	setPos(owner->pos());
}

void EntityBullet::tick(void) {
	age++;
	ai(this);
	handleMovement();
	if (borderCheck && !isOnScreen())
		deleteLater();
}
