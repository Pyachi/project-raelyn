#include "collectabletype.h"
#include "src/entity/collectable.h"
#include "src/assets/texture.h"
#include "src/assets/sfx.h"
#include "src/entity/player.h"

CollectableType::CollectableType(const Texture& texture,
																 const PlayerAI& onPickup)
		: texture(texture), onPickup(onPickup) {}

Collectable* CollectableType::spawn(const QPointF& loc) const {
	return new Collectable(this, loc);
}

const CollectableType CollectableType::POWER = CollectableType(
		Textures::PLAYERHITBOX,
		[](Player* player) { SFX::playSound(SFX::COLLECT_3, 0.25); });
