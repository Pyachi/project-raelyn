#include "entitybomb.h"
#include "entitybullet.h"
#include "game.h"

EntityBomb::EntityBomb(const Texture& tex,
											 const AI<EntityBomb>& ai,
											 const Entity* owner,
											 int damage)
		: Entity(BOMB, tex), ownerType(owner->type), damage(damage), ai(ai) {
	if (ownerType == EntityType::PLAYER)
		setOpacity(0.25);
	else if (ownerType == EntityType::ONLINEPLAYER)
		setOpacity(0.1);
	rotate(owner->rotation());
	setPos(owner->pos());
}

void EntityBomb::tick(void) {
	age++;
	ai(this);

	Map<UID, int> ignoreCopy = ignore;
	for (auto id : ignoreCopy) {
		ignore.erase(id.first);
		if (id.second != 0)
			ignore.insert({id.first, id.second - 1});
	}
	for (Entity* entity : getCollisions(BULLET)) {
		EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
		if (bullet->ownerType == ENEMY)
			bullet->deleteLater();
	}
	for (Entity* entity : getCollisions(ENEMY)) {
		if (!ignore.count(entity->id)) {
			entity->damage(damage);
			ignore.insert({entity->id, 60});
		}
	}
	handleMovement();
	setPos(confineToPlayableArea(pos()));
}

Entity* EntityBomb::getNearestEntity(EntityType type) const {
	Entity* closest = nullptr;
	double closestDistance = 99999999;
	for (auto entity : Game::getEntities()) {
		if (entity.second->type == type &&
				entity.second->distanceSquared(this) < closestDistance &&
				entity.second->isOnScreen() && !ignore.count(entity.second->id)) {
			closest = entity.second;
			closestDistance = entity.second->distanceSquared(this);
		}
	}
	return closest;
}
