#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

struct EnemyInfo;

class Enemy : public Entity {
 public:
	int health;

	void kill();

 private:
	Enemy(const EnemyInfo&, UUID);

	const AI<Enemy> ai;

	void tick() override;

	friend struct EnemyInfo;
};

#endif  // ENEMY_H
