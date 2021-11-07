#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include "alias.h"
#include "src/assets/texture.h"
#include <QPointF>

class Collectable;
class Player;

struct CollectableInfo {
	const Texture& texture;
	const AI<Player> onPickup;

	Collectable* spawn(const QPointF&) const;
};

namespace Collectables {
extern const CollectableInfo POWER;
extern const CollectableInfo POINTS;
extern const CollectableInfo HEALTH;
extern const CollectableInfo BOMB;
}

#endif  // COLLECTABLES_H
