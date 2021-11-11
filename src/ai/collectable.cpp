#include "collectable.h"
#include "src/assets/sfx.h"
#include "src/entity/entitycollectable.h"
#include "src/framework/game.h"

namespace Collectables {
EntityCollectable* spawn(Collectable collectable, const QPointF& loc) {
	EntityCollectable* entity;
	switch (collectable) {
		case COLLECTABLE_POWER:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POWER,
					[](EntityPlayer* player) { SFX::playSound(SFX_COLLECT3, 10); });
			break;
		case COLLECTABLE_POINTS:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POINTS,
					[](EntityPlayer* player) { SFX::playSound(SFX_COLLECT3, 10); });
			break;
		case COLLECTABLE_HEALTH:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POINTS,
					[](EntityPlayer* player) { SFX::playSound(SFX_COLLECT3, 10); });
			break;
		case COLLECTABLE_BOMB:
			entity = new EntityCollectable(
					TEXTURE_COLLECTABLE_POINTS,
					[](EntityPlayer* player) { SFX::playSound(SFX_COLLECT3, 10); });
			break;
	}
	entity->setPos(loc);
	return entity;
}
}  // namespace Collectables
