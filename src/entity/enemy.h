#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy;

class Enemies {
 public:
	static const Enemies ENEMY1;

	const Texture& texture;
	const EntityAI<Enemy> ai;
	const int health;

 private:
	Enemies(const Texture&, const EntityAI<Enemy>&, int);
};

class Enemy : public Entity {
 public:
	Enemy(const Enemies&, const QPointF&);

	int health;
	QPointF targetLoc;

	const QList<Bullet*> getHits();

 private:
	const EntityAI<Enemy> ai;
	void tick() override;
};

#endif  // ENEMY_H
