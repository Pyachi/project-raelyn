#ifndef PLAYERHITBOX_H
#define PLAYERHITBOX_H

#include "entity.h"

class PlayerHitbox : public BaseEntity {
 public:
	PlayerHitbox(BaseEntity*);

 private:
	const EntityAI<PlayerHitbox> ai;
	BaseEntity* owner;
	void tick() override;
};

#endif  // PLAYERHITBOX_H
