#include "enemytype.h"
#include "bulletpattern.h"
#include "src/entity/enemy.h"
#include "src/assets/texture.h"

Enemy* EnemyInfo::spawn(const QPointF& loc) const {
	return new Enemy(this, loc);
}

namespace Enemies {
const EnemyInfo ENEMYTEST{Textures::ENEMY1,
													[](Enemy* enemy) {
														if (enemy->cycle(50)) {
															enemy->fireBullet(BulletPatterns::SPRAY);
														}
													},
													50};
}
