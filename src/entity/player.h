#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "playerhitbox.h"

class Player : public Entity {
 public:
	Player(PlayerType, const QPointF&, const QString&);

	bool isHit();
	void setOnline();

 private:
	PlayerType type;
	QString user;
	bool firing;
	bool focus;
	int level;
	int power;
	bool online;

	PlayerHitbox hitbox;

	void tick() override;
};

#endif  // PLAYER_H
