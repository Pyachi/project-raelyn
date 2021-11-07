#include "collectable.h"
#include "player.h"
#include "enemy.h"
#include "src/game.h"
#include "src/ai/collectableai.h"
#include "bullet.h"
#include <QtMath>

Collectable::Collectable(const CollectableInfo& info)
		: Entity(COLLECTABLE, info.texture), onPickup(info.onPickup) {}

void Collectable::tick() {
	age++;
	int dir = rand() % 360;
	if (getAge() < 10)
		moveBy(20 * -sin(dir), 20 * cos(dir));
	else {
		Player* player = Game::getPlayer();
		if (player->distanceSquared(*this) < 150 * 150 || player->pos().y() < -200)
			moveTowardsPoint(player->pos(), 15);
		else
			moveBy(0, getAge() / 30.0);
		if (collidesWithItem(&player->hitbox)) {
			onPickup(player);
			deleteLater();
		}
	}
}
