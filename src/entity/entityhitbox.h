#ifndef PLAYERHITBOX_H
#define PLAYERHITBOX_H

#include "entity.h"

class EntityHitbox : public Entity {
	EntityHitbox();
	void tick() override;
	friend class EntityPlayer;
};

#endif  // PLAYERHITBOX_H
