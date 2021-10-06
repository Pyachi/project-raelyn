#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "src/assets/textures.h"

Enemy::Enemy(Game* game,
						 Texture texture,
						 QPoint spawn,
						 std::function<void(Enemy*)> ai,
						 int health)
		: BaseEntity(game, texture, spawn),
			AIEntity<Enemy>(game, texture, spawn, ai),
			CollidableEntity(game, texture, spawn) {
	this->health = health;
}

void Enemy::decHealth() {
	health--;
	if (health == 0)
		cleanup = true;
}

int Enemy::getHealth() {
	return health;
}

void Enemy::tick() {
	BaseEntity::tick();
	AIEntity::tick(this);
}

QList<CollidableEntity*> Enemy::getValidHits() {
	QList<CollidableEntity*> list;
	foreach (CollidableEntity* entity, getCollidingEntities()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Player*>(bullet->getOwner()))
				list.append(entity);
	}
	return list;
}
