#include "enemy.h"
#include <QtMath>
#include "bullet.h"
#include "collectable.h"
#include "player.h"
#include "src/resources.h"

const EntityAI<Enemy> MovementPatterns::NONE = [](Enemy* enemy) {};

const EntityAI<Enemy> MovementPatterns::LEFTRIGHTTEST = [](Enemy* enemy) {
	if (enemy->cycle(200, 100))
		enemy->targetLoc = QPointF(100, -300);
	else if (enemy->cycle(200, 0))
		enemy->targetLoc = QPointF(-100, -300);
};

const EntityAI<Enemy> FiringPatterns::ENEMY1 = [](Enemy* enemy) {
	if (enemy->cycle(50)) {
		enemy->fireBulletArc(Bullets::BASIC8, QPointF(0, 0), 5, -30, 30);
		enemy->fireBulletArc(Bullets::BASIC10, QPointF(0, 0), 5, -30, 30);
		enemy->fireBulletArc(Bullets::BASIC12, QPointF(0, 0), 5, -30, 30);
	}
};

Enemy::Enemy(const Texture& texture,
						 const EntityAI<Enemy>& movementAI,
						 const EntityAI<Enemy>& firingAI,
						 int health,
						 const QPointF& spawn)
		: Entity(texture, spawn),
			health(health),
			targetLoc(spawn),
			movementAI(movementAI),
			firingAI(firingAI) {}

const QList<Bullet*> Enemy::getHits() {
	QList<Bullet*> list;
	foreach(Entity * entity, getCollisions<Bullet>()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Player*>(bullet->owner))
				list.append(bullet);
	}
	return list;
}

void Enemy::tick() {
	timeAlive++;
	movementAI(this);
	firingAI(this);
	setPos(pos() + ((targetLoc - pos()) / 8));
	foreach(Bullet * bullet, getHits()) {
		Sound::playSound(SFX::EXPL_LIGHT_2, 0.1);
		health--;
		if (health == 0) {
			for (int i = 0; i < 10; i++)
				new Collectable(CollectableType::POWER, pos() + QPointF(0, 0));
			cleanup = true;
		}
		bullet->cleanup = true;
	}
}
