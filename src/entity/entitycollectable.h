#ifndef ENTITYCOLLECTABLE_H
#define ENTITYCOLLECTABLE_H

#include "entity.h"

class EntityPlayer;

class EntityCollectable : public Entity {
 public:
	EntityCollectable(const Texture& tex,
										const std::function<void(void)>& onPickup,
										int force = 1);

 private:
	double horz;
	double vert;
	const std::function<void(void)> onPickup;
	QGraphicsPixmapItem indicator;

	void tick(void) override;
};

#endif  // ENTITYCOLLECTABLE_H
