#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

struct CollectableInfo;
class Player;

class Collectable : public Entity {
	Collectable(const CollectableInfo&);

	const AI<Player> onPickup;

	void tick() override;

	friend struct CollectableInfo;
};

#endif  // COLLECTABLE_H
