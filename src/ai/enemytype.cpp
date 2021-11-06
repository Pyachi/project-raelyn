#include "enemytype.h"
#include "bulletpattern.h"
#include "src/entity/enemy.h"
#include "src/assets/texture.h"

EnemyType::EnemyType(const Texture& texture, const EnemyAI& ai, int health)
		: texture(texture), ai(ai), health(health) {}

Enemy* EnemyType::spawn(const QPointF& loc) const {
	return new Enemy(this, loc);
}

const EnemyType EnemyType::ENEMYTEST =
		EnemyType(Textures::ENEMY1, [](Enemy* enemy) {
			if (enemy->cycle(50)) {
				enemy->fireBullet(BulletPattern::SPRAY);
			}
		});
