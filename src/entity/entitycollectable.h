#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class EntityPlayer;

class EntityCollectable : public Entity {
 public:
	EntityCollectable(Tex, AI<EntityPlayer>);

 private:
	const AI<EntityPlayer> ai;

	void tick() override;
};

#endif  // COLLECTABLE_H
