#include "enemy.h"
#include "bulletpattern.h"
#include "src/entity/entityenemy.h"
#include "src/framework/game.h"

namespace Enemies {
EntityEnemy* spawn(Enemy enemy, UUID uuid, const QPointF& loc) {
	EntityEnemy* entity;
	switch (enemy) {
		// new EntityEnemy(TEXTURE, 'uuid', HEALTH, AI);
		case ENEMY_ENEMYTEST1:
			entity = new EntityEnemy(TEXENEMY1, uuid, 50, [](EntityEnemy* enemy) {
				if (enemy->cycle(50))
					enemy->fireBullets(PATTERN_SHOTGUN10X5);
			});
			break;
		case ENEMY_ENEMYTEST2:
			entity = new EntityEnemy(TEXENEMY1, uuid, 100, [](EntityEnemy* enemy) {
				if (enemy->getAge() < 60)
					enemy->moveBy(0, 1);
				if (enemy->getAge() == 60)
					enemy->deleteLater();
			});
	}
	entity->setPos(loc);
	return entity;
}
}  // namespace Enemies
