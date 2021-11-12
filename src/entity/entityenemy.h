#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

struct EnemyInfo;

enum MovementType {
	SMOOTH,
	QUICK
};

class EntityEnemy : public Entity {
 public:
	EntityEnemy(Texture, UID, int, AI<EntityEnemy>);

	int health;

	void moveTo(const QPointF&, int, MovementType = SMOOTH);

	void kill(void);

 private:
	const AI<EntityEnemy> ai;

	QPointF targetPos;
	int movementTicks;
	MovementType movementType;

	void tick(void) override;
};

#endif  // ENEMY_H
