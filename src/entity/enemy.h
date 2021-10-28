#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy;

using EnemyAI = EntityAI<Enemy>;

class Enemies {
 public:
	static const Enemies ENEMY1;

	const Texture& texture;
	const EnemyAI ai;
	const int health;

 private:
	Enemies(const Texture&, const EnemyAI&, int);
};

class Enemy : public BaseEntity {
 public:
	Enemy(const Enemies&, const QPointF&);

	int health;
	QPointF targetLoc;

	const QList<Bullet*> getHits();

 private:
	const EnemyAI ai;
	void tick() override;
};

#endif  // ENEMY_H
