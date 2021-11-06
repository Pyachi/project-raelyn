#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class EnemyInfo;
class Enemy;

using EnemyAI = std::function<void(Enemy*)>;

class Enemy : public Entity {
 public:
	QList<Bullet*> getHits();

 private:
	Enemy(const EnemyInfo*, const QPointF&);

	int health;

	const EnemyAI ai;

	void tick() override;

	friend class EnemyInfo;
};

#endif  // ENEMY_H
