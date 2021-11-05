#include "collectable.h"
#include <QtMath>
#include "player.h"
#include "playerhitbox.h"
#include "src/ai/collectabletype.h"

Collectable::Collectable(const CollectableType* type, const QPointF& spawn)
		: Entity(type->texture, spawn), onPickup(type->onPickup) {
	Game::addEntity(this);
}

void Collectable::tick() {
	age++;
	int dir = rand() % 360;
	if (getAge() < 10)
		moveBy(20 * -sin(dir), 20 * cos(dir));
	else {
		Player* player = getNearestEntity<Player>();
		if (player != nullptr &&
				(player->distanceSquared(this) < 150 * 150 || player->pos().y() < -200))
			moveTowardsPoint(player->pos(), 15);
		else
			moveBy(0, getAge() / 30.0);
		if (!getCollisions<PlayerHitbox>().isEmpty()) {
			onPickup(getNearestEntity<Player>());
			deleteLater();
		}
	}
}
