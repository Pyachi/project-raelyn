#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class CollectableInfo;
class Player;

using PlayerAI = std::function<void(Player*)>;

class Collectable : public Entity {
 private:
	Collectable(const CollectableInfo*, const QPointF&);

	const PlayerAI onPickup;

	void tick() override;

	friend class CollectableInfo;
};

#endif  // COLLECTABLE_H
