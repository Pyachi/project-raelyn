#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class EntityPlayer;

class EntityCollectable : public Entity {
 public:
	EntityCollectable(Texture tex, AI<EntityPlayer> onPickup);

 private:
	int dir;
	int speed;
	const AI<EntityPlayer> onPickup;

	void tick(void) override;
};

#endif  // COLLECTABLE_H
