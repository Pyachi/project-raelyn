#ifndef HITBOX_H
#define HITBOX_H

#include "src/entity/types/baseentity.h"
#include "src/entity/types/collidableentity.h"
#include "src/entity/types/linkedentity.h"

class PlayerHitbox : public LinkedEntity, public CollidableEntity {
 public:
	PlayerHitbox(Game*, Texture, BaseEntity*);

 private:
	void tick() override;
};

#endif  // HITBOX_H
