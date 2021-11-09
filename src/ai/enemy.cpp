#include "enemy.h"
#include "bulletpattern.h"
#include "src/entity/entityenemy.h"
#include "src/framework/game.h"

namespace Enemies {
EntityEnemy* spawn(Enemy enemy, UUID uuid, const QPointF& loc) {
	EntityEnemy* entity;
	switch (enemy) {
		case ENEMYTEST:
			entity = new EntityEnemy(TEXENEMY1, uuid, 50, [](EntityEnemy* enemy) {
				if (enemy->cycle(50))
					enemy->fireBullets(PATTERN_SHOTGUN10X5);
			});
	}
	entity->setPos(loc);
	return entity;
}
}  // namespace Enemies
