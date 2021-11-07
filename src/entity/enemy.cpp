#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "src/assets/sfx.h"
#include "src/ai/enemyai.h"
#include "src/ai/collectableai.h"

Enemy::Enemy(const EnemyInfo& info)
		: Entity(ENEMY, info.texture), health(info.health), ai(info.ai) {}

void Enemy::tick() {
	age++;
	ai(this);
	List<Bullet*> bullets;
	for (Entity* entity : getCollisions(BULLET)) {
		Bullet* bullet = dynamic_cast<Bullet*>(entity);
		if (bullet->ownerType == PLAYER)
			bullets.push_back(bullet);
	}
	for (Bullet* bullet : bullets) {
		SFX::playSound(SFX::EXPL_LIGHT_2, 0.1);
		health--;
		if (health == 0) {
			for (int i = 0; i < 10; i++)
				Collectables::POWER.spawn(pos());
			deleteLater();
		}
		bullet->deleteLater();
	}
}
