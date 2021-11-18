#include "entitybullet.h"

EntityBullet::EntityBullet(const Texture& tex,
                           const AI<EntityBullet>& ai,
													 const Entity* owner,
													 int damage)
    : Entity(BULLET, tex),
			ownerType(owner->type == BULLET
										? dynamic_cast<const EntityBullet*>(owner)->ownerType
										: owner->type),
      borderCheck(true),
			collisionCheck(true),
			damage(damage),
      ai(ai) {
	if (ownerType == EntityType::PLAYER)
    setOpacity(0.25);
	else if (ownerType == EntityType::ONLINEPLAYER)
    setOpacity(0.1);
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
