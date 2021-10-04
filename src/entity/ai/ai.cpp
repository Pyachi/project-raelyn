#include "ai.h"
#include "src/assets/textures.h"

std::function<void(Bullet*)> AI::playerBullet = [](Bullet* bullet) {
	bullet->moveBy(0, -40);
	QPointF pos = bullet->pos();
	if (bullet->borderCollision(pos))
		bullet->cleanup = true;
};

std::function<void(Bullet*)> AI::enemyBullet1 = [](Bullet* bullet) {
	bullet->moveFoward(5);
	bullet->setRotation(bullet->rotation() + 2);
	QPointF pos = bullet->pos();
	if (bullet->borderCollision(pos))
		bullet->cleanup = true;
};

std::function<void(Bullet*)> AI::enemyBullet2 = [](Bullet* bullet) {
	bullet->moveFoward(5);
	bullet->setRotation(bullet->rotation() - 2);
	QPointF pos = bullet->pos();
	if (bullet->borderCollision(pos))
		bullet->cleanup = true;
};

std::function<void(Bullet*)> AI::enemyBulletSpiral = [](Bullet* bullet) {
	if (bullet->time < 120) {
		bullet->moveFoward(5);
		bullet->setRotation(bullet->rotation() + 3);
	} else if (bullet->time < 2000) {
		QPointF pos(bullet->pos());
		if (bullet->borderCollision(pos))
			bullet->cleanup = true;
		bullet->moveFoward(10);
		bullet->setRotation(bullet->rotation() + 1);
	} else
		bullet->cleanup = true;
};

std::function<void(Enemy*)> AI::enemy = [](Enemy* enemy) {
	if (enemy->time % 10 == 0) {
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 0);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 30);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 60);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 90);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 120);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 150);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, 180);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, -30);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, -60);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, -90);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, -120);
		enemy->fireBullet(Textures::enemyBullet2, enemy->getCenter(),
											AI::enemyBulletSpiral, -150);
	}
	foreach (CollidableEntity* entity, enemy->getValidHits()) {
		enemy->decHealth();
		entity->cleanup = true;
	}
	if (enemy->getHealth() == 0)
		enemy->cleanup = true;
};
