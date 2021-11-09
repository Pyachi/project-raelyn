#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

struct EnemyInfo;

class EntityEnemy : public Entity {
 public:
	EntityEnemy(Tex, UUID, int, AI<EntityEnemy>);

	int health;

	void kill();

 private:
	const AI<EntityEnemy> ai;

	void tick() override;
};

#endif  // ENEMY_H
