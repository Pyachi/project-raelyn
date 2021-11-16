#include "entitycollectable.h"
#include "entityplayer.h"
#include "game.h"

EntityCollectable::EntityCollectable(const Texture& tex,
																		 const AI<EntityPlayer>& ai,
																		 int force)
		: Entity(COLLECTABLE, tex),
			horz((Random::getFloat(2) - 1) * force),
			vert(((Random::getFloat(2) - 1) * -force) - 2),
			onPickup(ai),
			indicator(Texture::ARROWRED, this) {
	setOpacity(0.5);
	indicator.setRotation(180);
	indicator.setOpacity(0.25);
	indicator.setOffset(-indicator.boundingRect().center());
}

void EntityCollectable::tick(void) {
	age++;
	if (pos().y() < -340) {
		indicator.show();
		indicator.setPos(mapFromParent({pos().x(), -330}));
	} else
		indicator.hide();
	if (age <= 20) {
		rotate(18);
		moveBy(horz, vert);
	}
	if (age > 60) {
		EntityPlayer* player = Game::getPlayer();
		if (player != nullptr && (player->distanceSquared(this) < 150 * 150 ||
															player->pos().y() < -200)) {
			moveTowardsPoint(player->pos(), 15);
			horz = 0;
			vert = 0;
		} else
			moveBy(horz, vert);
		if (collidesWithItem(player)) {
			onPickup(player);
			deleteLater();
		}
	} else
		moveBy(horz, vert);
	if (!isOnScreen() && pos().y() > 0)
		deleteLater();
	else if (pos().x() > 266 || pos().x() < -266)
		horz *= -1;
	vert += 0.03;
}
