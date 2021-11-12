#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class EntityBullet : public Entity {
 public:
	EntityBullet(Texture tex, AI<EntityBullet> ai, const Entity* owner);

	const EntityType ownerType;
	bool borderCheck;
	int damage;

 private:
	const AI<EntityBullet> ai;

	void tick(void) override;
};

#endif  // BULLET_H
