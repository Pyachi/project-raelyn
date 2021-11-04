#include "enemy.h"
#include <QtMath>
#include "bullet.h"
#include "collectable.h"
#include "player.h"
#include "src/resources.h"

Enemies::Enemies(const Texture& texture, const EntityAI<Enemy>& ai, int health)
		: texture(texture), ai(ai), health(health) {}

const Enemies Enemies::ENEMY1 = Enemies(
		Texture::ENEMY1,
		[](Enemy* enemy) {
			if (enemy->cycle(5))
				enemy->fireBulletCircle(Bullets::FLOWER, QPointF(0, 0), 2,
																pow(enemy->timeAlive / 10.0, 2));
		},
		50);

Enemy::Enemy(const Enemies& info, const QPointF& spawn)
		: Entity(info.texture, spawn),
			health(info.health),
			targetLoc(spawn),
			ai(info.ai) {}

const QList<Bullet*> Enemy::getHits() {
	QList<Bullet*> list;
	foreach (Entity* entity, getCollisions<Bullet>()) {
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
