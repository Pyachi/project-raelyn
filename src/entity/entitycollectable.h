#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class EntityPlayer;

class EntityCollectable : public Entity {
 public:
	EntityCollectable(Texture, AI<EntityPlayer>);

 private:
	const AI<EntityPlayer> ai;

	void tick(void) override;
};

#endif  // COLLECTABLE_H
