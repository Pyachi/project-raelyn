#ifndef PLAYERHITBOX_H
#define PLAYERHITBOX_H

#include "entity.h"

class PlayerHitbox : public Entity {
	PlayerHitbox();
	void tick() override;
	friend class Player;
};

#endif  // PLAYERHITBOX_H
