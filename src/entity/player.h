#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "playerhitbox.h"
#include "src/ai/playerai.h"

class Player : public Entity {
 public:
	Player(PlayerType, const QString&);

	void tick() override;

	PlayerHitbox hitbox;

 private:
	PlayerType playerType;
	QString user;
	bool firing;
	bool focus;
	int level;
	int power;
};

#endif  // PLAYER_H
