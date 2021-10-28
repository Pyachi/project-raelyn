#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player;
class PlayerHitbox;

class Players {
 public:
	static const Players PYACHI;
	static const Players AERON;

	const Texture& texture;
	const EntityAI<Player> firingPattern;
	const int speed;
	const int focusSpeed;

 private:
	Players(const Texture&, const EntityAI<Player>&, int, int);
};

class Player : public BaseEntity {
 public:
	Player(const Players&, const QPointF&);

	bool firing;
	bool focus;
	int level;

	bool isHit();

 private:
	const int normalSpeed;
	const int focusSpeed;
	const EntityAI<Player> firingPattern;
	const EntityAI<Player> ai;
	PlayerHitbox* hitbox;
	void tick() override;
};

#endif  // PLAYER_H
