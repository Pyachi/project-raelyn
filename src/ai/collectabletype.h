#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include <QPointF>
#include <functional>

class Texture;
class Player;
class Collectable;

using PlayerAI = std::function<void(Player*)>;

struct CollectableInfo {
	const Texture& texture;
	const PlayerAI onPickup;

	Collectable* spawn(const QPointF&) const;
};

namespace Collectables {
extern const CollectableInfo POWER;
extern const CollectableInfo POINTS;
extern const CollectableInfo HEALTH;
extern const CollectableInfo BOMB;
}

#endif  // COLLECTABLES_H
