#include "entitybullet.h"

EntityBullet::EntityBullet(const Texture& tex,
                           const AI<EntityBullet>& ai,
													 const Entity* owner,
													 int damage)
    : Entity(BULLET, tex),
      ownerType(owner->type),
      borderCheck(true),
			damage(ownerType == ONLINEPLAYER ? 0 : damage),
      ai(ai) {
	if (owner->type == EntityType::PLAYER)
    setOpacity(0.25);
	else if (owner->type == EntityType::ONLINEPLAYER)
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
