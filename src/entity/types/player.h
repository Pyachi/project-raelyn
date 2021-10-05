#ifndef PLAYER_H
#define PLAYER_H

#include <QSet>
#include "src/entity/types/baseentity.h"
#include "src/entity/types/collidableentity.h"

class PlayerHitbox;

class Player : public BaseEntity {
 public:
	Player(Game*);

	QList<CollidableEntity*> getValidHits();

 private:
	PlayerHitbox* hitbox;
	bool firing = false;
	bool focus = false;
	int level = 1;

	void tick() override;
	void checkMovement(const QSet<int>& keys);
	void shootBullets();
	void fireBullet(int, int);
};

#endif  // PLAYER_H
