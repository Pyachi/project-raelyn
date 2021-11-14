#include "entitycollectable.h"
#include "Framework"
#include "Entity"

EntityCollectable::EntityCollectable(Texture tex,
																		 AI<EntityPlayer> ai,
																		 bool random)
		: Entity(COLLECTABLE, tex),
			dir(random ? Random::getInt() % 360 : 0),
			speed(random ? ((Random::getInt() % 20) - 10) +
												 ((Random::getInt() % 20) - 10)
									 : 0),
			onPickup(ai) {}

void EntityCollectable::tick(void) {
	age++;
	if (age <= 20) {
		rotate(18);
	}
	if (age <= 5) {
		moveBy(speed * cos(dir), speed * sin(dir));
	}
	if (age > 5) {
		EntityPlayer* player = Game::getPlayer();
		if (player != nullptr &&
				(player->distanceSquared(this) < 150 * 150 || player->pos().y() < -200))
			moveTowardsPoint(player->pos(), 15);
		else
			moveBy(0, (getAge() - 60.0) / 30.0);
		if (!isOnScreen() && pos().y() > 0)
			deleteLater();
		if (collidesWithItem(player)) {
			onPickup(player);
			deleteLater();
		}
	}
}
