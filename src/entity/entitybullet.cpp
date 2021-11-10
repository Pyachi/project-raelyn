#include "entitybullet.h"
#include "src/ai/bullet.h"
#include "src/framework/game.h"

EntityBullet::EntityBullet(Texture tex,
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

void EntityBullet::tick(void) {
	age++;
	ai(this);
	if (borderCheck && !isOnScreen())
		deleteLater();
}
