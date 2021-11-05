#include "collectabletype.h"
#include "src/entity/collectable.h"
#include "assets.h"
#include "src/entity/player.h"

CollectableType::CollectableType(const Texture& texture,
																 const PlayerAI& onPickup)
		: texture(texture), onPickup(onPickup) {}

Collectable* CollectableType::spawn(const QPointF& loc) const {
	return new Collectable(this, loc);
}

const CollectableType CollectableType::POWER = CollectableType(
		Texture::PLAYERHITBOX,
		[](Player* player) { Sound::playSound(SFX::COLLECT_3, 0.25); });
