#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class EntityBullet : public Entity {
 public:
	EntityBullet(Tex, AI<EntityBullet>, EntityType, int);

	const EntityType ownerType;
	bool borderCheck;
	int damage;

 private:
	const AI<EntityBullet> ai;

	void tick(void) override;
};

#endif  // BULLET_H
