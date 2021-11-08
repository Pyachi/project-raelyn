#include "enemyai.h"
#include "bulletpattern.h"
#include "src/framework/game.h"
#include "src/entity/enemy.h"

Enemy* EnemyInfo::spawn(const QPointF& loc, UUID id) const {
	Enemy* enemy = new Enemy(*this, id);
	enemy->setPos(loc);
	return enemy;
}

namespace Enemies {
const EnemyInfo get(EnemyType type) {
	switch (type) {
		case ENEMYTEST:
			return {Textures::ENEMY1, [](Enemy* enemy) {
																	if (enemy->cycle(50))
																		enemy->fireBullets(BulletPatterns::SPRAY);
																},
							50};
	}
}
}
