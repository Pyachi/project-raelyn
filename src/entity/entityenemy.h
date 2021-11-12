#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class EntityEnemy : public Entity {
 public:
	EntityEnemy(Texture tex, UID id, int health, AI<EntityEnemy> ai);

	int health;

	void kill(void);

 private:
	const AI<EntityEnemy> ai;

	void tick(void) override;
};

#endif  // ENEMY_H
