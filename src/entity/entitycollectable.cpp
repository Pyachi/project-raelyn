#include "entitycollectable.h"
#include "Framework"
#include "Entity"

EntityCollectable::EntityCollectable(Texture tex, AI<EntityPlayer> ai)
		: Entity(COLLECTABLE, tex), onPickup(ai) {}

void EntityCollectable::tick(void) {
	age++;
	if (getAge() == 1) {
		dir = Random::getInt() % 360;
		speed = ((Random::getInt() % 60) - 30) + ((Random::getInt() % 60) - 30);
	} else if (getAge() < 5) {
		moveBy(speed * cos(dir), speed * sin(dir));
	} else {
		EntityPlayer* player = Game::getPlayer();
		if (player != nullptr &&
				(player->distanceSquared(this) < 150 * 150 || player->pos().y() < -200))
			moveTowardsPoint(player->pos(), 15);
		else
			moveBy(0, getAge() / 30.0);
		if (!isOnScreen() && pos().y() > 0)
			deleteLater();
		if (collidesWithItem(player)) {
			onPickup(player);
			deleteLater();
		}
	}
}
