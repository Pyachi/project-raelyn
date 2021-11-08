#include "collectableai.h"
#include "src/framework/game.h"
#include "src/assets/sfx.h"
#include "src/entity/collectable.h"

Collectable* CollectableInfo::spawn(const QPointF& loc) const {
	Collectable* collectable = new Collectable(*this);
	collectable->setPos(loc);
	return collectable;
}

namespace Collectables {
const CollectableInfo POWER{Textures::PLAYERHITBOX, [](Player* player) {
	SFX::playSound(SFX::COLLECT_3, 0.25);
}};
const CollectableInfo POINTS{Textures::PLAYERHITBOX, [](Player* player) {
	SFX::playSound(SFX::COLLECT_3, 0.25);
}};
const CollectableInfo HEALTH{Textures::PLAYERHITBOX, [](Player* player) {
	SFX::playSound(SFX::COLLECT_3, 0.25);
}};
const CollectableInfo BOMB{Textures::PLAYERHITBOX, [](Player* player) {
	SFX::playSound(SFX::COLLECT_3, 0.25);
}};
}
