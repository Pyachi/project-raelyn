#include "enemy.h"
#include "bullet.h"
#include "player.h"

Enemy::Enemy(Game* game, const EnemyInfo& info, const QPointF& spawn)
		: AIEntity<Enemy>(game, info.texture, info.ai, spawn),
			CollidableEntity(),
			health(info.health),
			targetLoc(spawn) {}

const QList<Bullet*> Enemy::getHits() {
	QList<Bullet*> list;
	foreach (BaseEntity* entity, getCollisions()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Player*>(bullet->owner))
				list.append(bullet);
	}
	return list;
}

void Enemy::tick() {
	timeAlive++;
	ai(this);
	setPos(pos() + ((targetLoc - pos()) / 8));
	foreach (Bullet* bullet, getHits()) {
		health--;
		if (health == 0)
			cleanup = true;
		bullet->cleanup = true;
	}
}
