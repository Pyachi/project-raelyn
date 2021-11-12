#include "collectable.h"
#include "Assets"
#include "Entity"

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
