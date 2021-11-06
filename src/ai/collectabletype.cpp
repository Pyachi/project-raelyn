#include "collectabletype.h"
#include "src/entity/collectable.h"
#include "src/assets/texture.h"
#include "src/assets/sfx.h"
#include "src/entity/player.h"

Collectable* CollectableInfo::spawn(const QPointF& loc) const {
	return new Collectable(this, loc);
}

namespace Collectables {
const CollectableInfo POWER{Textures::PLAYERHITBOX, [](Player* player) {
	SFX::playSound(SFX::COLLECT_3, 0.25);
}};
}
