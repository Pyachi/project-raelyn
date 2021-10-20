#ifndef PLAYERHITBOX_H
#define PLAYERHITBOX_H

#include "entitytypes.h"

class PlayerHitbox : public AIEntity<PlayerHitbox>,
										 public LinkedEntity,
										 public CollidableEntity {
 public:
	PlayerHitbox(Game*, BaseEntity*);

	void tick() override;
};

#endif  // PLAYERHITBOX_H
