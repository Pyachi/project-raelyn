#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "playerhitbox.h"

class Player : public Entity {
 public:
	Player(PlayerType, const QPointF&, const QString&);

	bool isHit();

	void tick() override;

	PlayerHitbox hitbox;

 private:
	PlayerType type;
	QString user;
	bool firing;
	bool focus;
	int level;
	int power;
};

#endif  // PLAYER_H
