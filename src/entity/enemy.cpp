#include "enemy.h"
#include <QtMath>
#include "bullet.h"
#include "player.h"
#include "src/entity/collectable.h"
#include "src/resources.h"

const EnemyAI MovementPatterns::NONE = [](Enemy* enemy) {};

const EnemyAI MovementPatterns::LEFTRIGHTTEST = [](Enemy* enemy) {
	if (enemy->cycle(200, 100))
		enemy->targetLoc = QPointF(100, -300);
	else if (enemy->cycle(200, 0))
		enemy->targetLoc = QPointF(-100, -300);
};

const EnemyAI FiringPatterns::ENEMY1 = [](Enemy* enemy) {
	if (enemy->cycle(50)) {
		enemy->fireBulletArc(Bullets::BASIC8, QPointF(0, 0), 5, -30, 30);
		enemy->fireBulletArc(Bullets::BASIC10, QPointF(0, 0), 5, -30, 30);
		enemy->fireBulletArc(Bullets::BASIC12, QPointF(0, 0), 5, -30, 30);
	}
};

Enemy::Enemy(const Texture& texture,
						 const EnemyAI& movementAI,
						 const EnemyAI& firingAI,
						 int health,
						 const QPointF& spawn)
		: BaseEntity(texture, spawn),
			health(health),
			targetLoc(spawn),
			movementAI(movementAI),
			firingAI(firingAI) {}

const QList<Bullet*> Enemy::getHits() {
	QList<Bullet*> list;
	foreach(BaseEntity * entity, getCollisions<Bullet>()) {
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
		Sound::playSound(SFX::EXPL_SUPERHEAVY_2, 1);
		health--;
		if (health == 0) {
			for (int i = 0; i < 10; i++)
				new Collectable(CollectableType::POWER, pos() + QPointF(0, 0));
			Game::GAME->screenShake();
			cleanup = true;
		}
		bullet->cleanup = true;
	}
}
