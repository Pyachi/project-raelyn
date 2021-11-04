#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy;

class MovementPatterns {
 public:
	static const EntityAI<Enemy> NONE;
	static const EntityAI<Enemy> LEFTRIGHTTEST;  // Demo
};

class FiringPatterns {
 public:
	static const EntityAI<Enemy> ENEMY1;  // Demo
};

class Enemy : public Entity {
 public:
	Enemy(const Texture&,
				const EntityAI<Enemy>&,
				const EntityAI<Enemy>&,
				int,
				const QPointF&);

	int health;
	QPointF targetLoc;

	const QList<Bullet*> getHits();

 private:
	const EntityAI<Enemy> movementAI;
	const EntityAI<Enemy> firingAI;
	void tick() override;
};

#endif  // ENEMY_H
