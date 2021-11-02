#include "collectable.h"
#include <QtMath>
#include "bullet.h"
#include "player.h"
#include "playerhitbox.h"

CollectableType::CollectableType(const Texture& texture,
																 const EntityAI<Player>& onPickup)
		: texture(texture), onPickup(onPickup) {}

Collectable::Collectable(const CollectableType& type, const QPointF& spawn)
		: BaseEntity(type.texture, spawn),
			ai([](Collectable* entity) {
				int dir = rand() % 360;
				if (entity->timeAlive < 10)
					entity->moveBy(20 * -sin(dir), 20 * cos(dir));
				else {
					if (entity->getNearestEntity<Player>()->distanceSquared(entity) <
									150 * 150 ||
							entity->getNearestEntity<Player>()->pos().y() < -200)
						entity->moveTowardsPoint(entity->getNearestEntity<Player>()->pos(),
																		 15);
					else
						entity->moveBy(0, entity->timeAlive / 30.0);
					if (!entity->getCollisions<PlayerHitbox>().isEmpty()) {
						entity->onPickup(entity->getNearestEntity<Player>());
						entity->cleanup = true;
					}
				}
			}),
			onPickup(type.onPickup) {}

const CollectableType CollectableType::POWER =
		CollectableType(Texture::PLAYERHITBOX,
										[](Player* player) { player->power++; });

void Collectable::tick() {
	timeAlive++;
	ai(this);
}
