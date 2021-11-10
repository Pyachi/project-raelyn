#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

struct EnemyInfo;

class EntityEnemy : public Entity {
 public:
	EntityEnemy(Texture, UUID, int, AI<EntityEnemy>);

	int health;

	void kill(void);

 private:
	const AI<EntityEnemy> ai;

	void tick(void) override;
};

#endif  // ENEMY_H
