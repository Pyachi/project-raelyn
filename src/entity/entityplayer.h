#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "entityhitbox.h"
#include "src/ai/player.h"

class EntityPlayer : public Entity {
 public:
	EntityPlayer(PlayerType, const QString&, UUID, EntityType = PLAYER);

	void tick() override;

	EntityHitbox hitbox;
	const PlayerType playerType;

	List<EntityBullet*> fireBullets(const List<BulletInfo>&,
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
