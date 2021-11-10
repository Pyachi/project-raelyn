#include "collectable.h"
#include "src/assets/sfx.h"
#include "src/entity/entitycollectable.h"
#include "src/framework/game.h"

namespace Collectables {
EntityCollectable* spawn(Collectable collectable, const QPointF& loc) {
	EntityCollectable* entity;
	switch (collectable) {
		case POWER:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POWER,
					[](EntityPlayer* player) { SFX::playSound(COLLECT_3, 0.25); });
			break;
		case POINTS:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POINTS,
					[](EntityPlayer* player) { SFX::playSound(COLLECT_3, 0.25); });
			break;
		case HEALTH:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POINTS,
					[](EntityPlayer* player) { SFX::playSound(COLLECT_3, 0.25); });
			break;
		case BOMB:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POINTS,
					[](EntityPlayer* player) { SFX::playSound(COLLECT_3, 0.25); });
			break;
	}
	entity->setPos(loc);
	return entity;
}
}  // namespace Collectables
