#include "entitybullet.h"
#include "src/ai/bullet.h"
#include "src/framework/game.h"

EntityBullet::EntityBullet(Tex tex,
													 AI<EntityBullet> ai,
													 EntityType ownerType,
													 int damage)
		: Entity(BULLET, tex),
			ownerType(ownerType),
			borderCheck(true),
			damage(damage),
			ai(ai) {
	Game::addEntity(this);
}

void EntityBullet::tick() {
	age++;
	ai(this);
	if (borderCheck && !isOnScreen())
		deleteLater();
}
