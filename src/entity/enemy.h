#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

struct EnemyInfo;

class Enemy : public Entity {
 public:
	int health;

 private:
	Enemy(const EnemyInfo&);

	const AI<Enemy> ai;

	void tick() override;

	friend struct EnemyInfo;
};

#endif  // ENEMY_H
