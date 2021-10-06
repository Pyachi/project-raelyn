#ifndef ENTITIES_H
#define ENTITIES_H

#include "entitytypes.h"

class PlayerInfo;
class EnemyInfo;
class BulletInfo;

class Player : public BaseEntity {
 public:
	void tick() override;

 private:
	Player(Game*, PlayerInfo*, QPointF);

	friend class PlayerInfo;
};

class Enemy : public BaseEntity,
							public CollidableEntity,
							public AIEntity<Enemy> {
 public:
	void tick() override;

 private:
	Enemy(Game*, EnemyInfo*, QPointF);

	int health;

	friend class EnemyInfo;
};

class Bullet : public BaseEntity,
							 public LinkedEntity,
							 public CollidableEntity,
							 public AIEntity<Bullet> {
 public:
	void tick() override;

 private:
	Bullet(Game*, BulletInfo*, BaseEntity*, QPointF, qreal);

	friend class BulletInfo;
};

class PlayerHitbox : public BaseEntity,
										 public LinkedEntity,
										 public CollidableEntity {
 public:
	void tick() override;

 private:
	PlayerHitbox(Game*, BaseEntity*);

	friend class Player;
};

#endif  // ENTITIES_H
