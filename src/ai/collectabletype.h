#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include <QPointF>

class Texture;
class Player;
class Collectable;

using PlayerAI = std::function<void(Player*)>;

class CollectableType {
 public:
	static const CollectableType POWER;
	static const CollectableType POINTS;
	static const CollectableType HEALTH;
	static const CollectableType BOMB;

	const Texture& texture;
	const PlayerAI onPickup;

	Collectable* spawn(const QPointF&) const;

 private:
	CollectableType(const Texture&, const PlayerAI&);
};

#endif  // COLLECTABLES_H
