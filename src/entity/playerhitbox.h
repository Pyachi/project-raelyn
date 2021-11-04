#ifndef PLAYERHITBOX_H
#define PLAYERHITBOX_H

#include "entity.h"

class PlayerHitbox : public Entity {
 public:
	PlayerHitbox(Entity*);
	Entity* owner;

 private:
	const EntityAI<PlayerHitbox> ai;
	void tick() override;
};

#endif  // PLAYERHITBOX_H
