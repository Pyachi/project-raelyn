#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "entityhitbox.h"
#include "src/ai/player.h"

class EntityPlayer : public Entity {
 public:
	EntityPlayer(PlayerType, const QString&, UID, EntityType = PLAYER);

	void tick(void) override;

	EntityHitbox hitbox;
	const PlayerType playerType;

	List<EntityBullet*> fireBullets(Pattern,
																	Texture,
																	double = 0,
																	const QPointF& = {0, 0},
																	int = 1);

 private:
	QString user;
	bool firing;
	bool focus;
	int level;
	int power;
};

#endif  // PLAYER_H
