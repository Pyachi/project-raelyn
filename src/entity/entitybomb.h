#ifndef ENTITYBOMB_H
#define ENTITYBOMB_H

#include "entity.h"
#include "uid.h"

class EntityBomb : public Entity {
 public:
	EntityBomb(const Texture& tex,
						 const AI<EntityBomb>& ai,
						 const Entity* owner,
						 int damage);

	EntityType ownerType;
	const int damage;

	Entity* getNearestEntity(EntityType type) const;

 private:
	const AI<EntityBomb> ai;
	Map<UID, int> ignore;

	void tick(void) override;
};

struct BombInfo {
	BombInfo(const AI<EntityBomb>& ai,
					 const Texture& tex,
					 int scale = 1,
					 int damage = 1)
			: ai(ai), tex(tex), scale(scale), damage(damage) {}
	const AI<EntityBomb> ai;
	const Texture& tex;
	const int scale;
	const int damage;
};

#endif  // ENTITYBOMB_H
