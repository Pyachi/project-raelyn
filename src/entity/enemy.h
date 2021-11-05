#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class EnemyType;
class Enemy;

using EnemyAI = std::function<void(Enemy*)>;

class Enemy : public Entity {
 public:
	QList<Bullet*> getHits();

 private:
	Enemy(const EnemyType*, const QPointF&);

	int health;

	const EnemyAI ai;

	void tick() override;

	friend class EnemyType;
};

#endif  // ENEMY_H
