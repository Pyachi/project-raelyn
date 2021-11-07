#include "enemyai.h"
#include "bulletpattern.h"
#include "src/entity/enemy.h"

Enemy* EnemyInfo::spawn(const QPointF& loc) const {
	Enemy* enemy = new Enemy(*this);
	enemy->setPos(loc);
	Game::addEntity(enemy);
	return enemy;
}

namespace Enemies {
const EnemyInfo ENEMYTEST{Textures::ENEMY1,
													[](Enemy* enemy) {
														if (enemy->cycle(50))
															enemy->fireBullets(BulletPatterns::SPRAY);
													},
													50};
}
