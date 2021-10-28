#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "entity.h"

class Collectable;

using CollectableAI = EntityAI<Collectable>;

class CollectableType {
 public:
	static const CollectableType POWER;
	static const CollectableType POINTS;
	static const CollectableType HEALTH;
	static const CollectableType BOMB;

	const Texture& texture;
	const CollectableAI ai;

 private:
	CollectableType(const Texture&, const CollectableAI&);
};

class Collectable : public BaseEntity {
 public:
	Collectable(const CollectableType&, const QPointF&);

 private:
	const CollectableAI ai;
	void tick() override;
};

#endif  // COLLECTABLE_H
