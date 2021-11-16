#ifndef ENTITYCOLLECTABLE_H
#define ENTITYCOLLECTABLE_H

#include "entity.h"

class EntityPlayer;

class EntityCollectable : public Entity {
 public:
	EntityCollectable(const Texture& tex,
										const AI<EntityPlayer>& onPickup,
										int force = 1);

 private:
	float horz;
	float vert;
	const AI<EntityPlayer> onPickup;
	QGraphicsPixmapItem indicator;

	void tick(void) override;
};

#endif  // ENTITYCOLLECTABLE_H
