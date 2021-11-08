#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "playerhitbox.h"
#include "src/ai/playerai.h"

class Player : public Entity {
 public:
	Player(PlayerType, const QString&, UUID, EntityType = PLAYER);

	void tick() override;

	PlayerHitbox hitbox;
	const PlayerType playerType;

	List<Bullet*> fireBullets(const List<BulletInfo>&,
														double = 0,
														const QPointF& = QPointF(0, 0));

 private:
	QString user;
	bool firing;
	bool focus;
	int level;
	int power;
};

#endif  // PLAYER_H
