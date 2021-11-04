#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy;

class MovementPatterns {
 public:
	static const EnemyAI NONE;
	static const EnemyAI LEFTRIGHTTEST;  // Demo
};

class FiringPatterns {
 public:
	static const EnemyAI ENEMY1;  // Demo
};

class Enemy : public Entity {
 public:
	Enemy(const Texture&, const EnemyAI&, const EnemyAI&, int, const QPointF&);

	int health;
	QPointF targetLoc;

	const QList<Bullet*> getHits();

 private:
	const EnemyAI movementAI;
	const EnemyAI firingAI;
	void tick() override;
};

#endif  // ENEMY_H
