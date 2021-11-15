#include "entitybullet.h"

EntityBullet::EntityBullet(const Texture& tex,
                           const AI<EntityBullet>& ai,
                           const Entity* owner)
    : Entity(BULLET, tex),
      ownerType(owner->type),
      borderCheck(true),
      damage(1),
      ai(ai) {
  if (owner->type == EntityType::PLAYER) {
    setOpacity(0.25);
  } else if (owner->type == EntityType::ONLINEPLAYER) {
    damage = 0;
    setOpacity(0.1);
  }
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
