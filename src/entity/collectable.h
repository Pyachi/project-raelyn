#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class Collectable;
class Player;

class CollectableType {
 public:
	static const CollectableType POWER;
	static const CollectableType POINTS;
	static const CollectableType HEALTH;
	static const CollectableType BOMB;

	const Texture& texture;
	const EntityAI<Player> onPickup;

 private:
	CollectableType(const Texture&, const EntityAI<Player>&);
};

class Collectable : public BaseEntity {
 public:
	Collectable(const CollectableType&, const QPointF&);

 private:
	const EntityAI<Collectable> ai;
	const EntityAI<Player> onPickup;
	void tick() override;
};

#endif  // COLLECTABLE_H
