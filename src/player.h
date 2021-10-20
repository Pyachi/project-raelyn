#ifndef PLAYER_H
#define PLAYER_H

#include "entityinfo.h"

class Player : public AIEntity<Player> {
 public:
	Player(Game*, const PlayerInfo&, const QPointF&);

	bool firing;
	bool focus;
	int level;

 private:
	const int normalSpeed;
	const int focusSpeed;
	const FiringPattern firingPattern;

	PlayerHitbox* hitbox;

	bool isHit();

	void tick() override;
};

#endif  // PLAYER_H
