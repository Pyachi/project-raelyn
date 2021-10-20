#ifndef ENEMY_H
#define ENEMY_H

#include "entityinfo.h"

class Enemy : public AIEntity<Enemy>, public CollidableEntity {
 public:
	Enemy(Game*, const EnemyInfo&, const QPointF&);

	int health;
	QPointF targetLoc;

	const QList<Bullet*> getHits();

	void tick() override;
};

#endif  // ENEMY_H
