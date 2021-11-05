#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class CollectableType;
class Player;

using PlayerAI = std::function<void(Player*)>;

class Collectable : public Entity {
 private:
	Collectable(const CollectableType*, const QPointF&);

	const PlayerAI onPickup;

	void tick() override;

	friend class CollectableType;
};

#endif  // COLLECTABLE_H
