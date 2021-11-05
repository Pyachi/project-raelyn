#include "enemy.h"
#include "src/ai/enemytype.h"
#include "src/entity/bullet.h"
#include "assets.h"
#include "src/entity/player.h"
#include "src/ai/collectabletype.h"

Enemy::Enemy(const EnemyType* info, const QPointF& spawn)
		: Entity(info->texture, spawn), health(info->health), ai(info->ai) {
	Game::addEntity(this);
}

QList<Bullet*> Enemy::getHits() {
	QList<Bullet*> list;
	foreach(Bullet * bullet, getCollisions<Bullet>()) {
		if (dynamic_cast<Player*>(bullet->owner))
			list.append(bullet);
	}
	return list;
}

void Enemy::tick() {
	age++;
	ai(this);
	foreach(Bullet * bullet, getHits()) {
		Sound::playSound(SFX::EXPL_LIGHT_2, 0.1);
		health--;
		if (health == 0) {
			for (int i = 0; i < 10; i++)
				CollectableType::POWER.spawn(pos());
			deleteLater();
		}
		bullet->deleteLater();
	}
}
