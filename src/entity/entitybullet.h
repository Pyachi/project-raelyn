#ifndef ENITTYBULLET_H
#define ENTITYBULLET_H

#include "entity.h"

class EntityBullet : public Entity {
 public:
  EntityBullet(const Texture& tex,
               const AI<EntityBullet>& ai,
							 const Entity* owner,
							 int damage);

	EntityType ownerType;
  bool borderCheck;
	bool collisionCheck;
	const int damage;

 private:
  const AI<EntityBullet> ai;

  void tick(void) override;
};

#endif  // ENTITYBULLET_H
