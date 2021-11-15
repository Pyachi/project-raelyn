#ifndef ENTITYCOLLECTABLE_H
#define ENTITYCOLLECTABLE_H

#include "entity.h"

class EntityPlayer;

class EntityCollectable : public Entity {
 public:
  EntityCollectable(const Texture& tex, const AI<EntityPlayer>& onPickup);

 private:
  const AI<EntityPlayer> onPickup;

  void tick(void) override;
};

#endif  // ENTITYCOLLECTABLE_H
