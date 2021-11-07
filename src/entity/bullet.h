#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

struct BulletInfo;

class Bullet : public Entity {
 public:
	EntityType ownerType;
	bool borderCheck;

 private:
	Bullet(const BulletInfo*, const Entity*);

	const AI<Bullet>& ai;

	void tick() override;

	friend struct BulletInfo;
};

#endif  // BULLET_H
