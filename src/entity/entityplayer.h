#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "player.h"

class EntityPlayer : public Entity {
 public:
	EntityPlayer(PlayerType playerType,
							 const QString& name,
							 UID id,
							 EntityType type = PLAYER);

	void tick(void) override;

	QGraphicsPixmapItem hitbox;
	const PlayerType playerType;

	EntityBullet* fireBullet(BulletInfo info,
													 BulletAI ai,
													 Texture tex,
													 double rot = 0,
													 const QPointF& loc = {0, 0},
													 int scale = 1,
													 int damage = 1);

 private:
	QGraphicsSimpleTextItem display;
	QString name;
	bool firing;
	bool focus;
	int level;
	int power;
	int health;
	int invFrames;
};

#endif  // PLAYER_H
