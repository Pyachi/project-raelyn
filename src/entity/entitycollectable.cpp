#include "entitycollectable.h"
#include "entityplayer.h"
#include "game.h"

EntityCollectable::EntityCollectable(const Texture& tex,
																		 const AI<EntityPlayer>& ai)
		: Entity(COLLECTABLE, tex), onPickup(ai) {}

void EntityCollectable::tick(void) {
	age++;
	if (age <= 20) {
		rotate(18);
	}
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
