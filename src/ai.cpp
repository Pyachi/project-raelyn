#include "ai.h"
#include "entities.h"

EntityAI<Bullet> AI::playerBullet1 = [](Bullet* bullet) {
	bullet->moveBy(0, -40);
	if (!bullet->isVisible())
		bullet->cleanup = true;
};

EntityAI<Bullet> AI::enemyBullet1 = [](Bullet* bullet) {
	if (bullet->time < 120) {
		bullet->moveFoward(5);
		bullet->setRotation(bullet->rotation() + 3);
	} else if (bullet->time < 2000) {
		if (!bullet->isVisible())
			bullet->cleanup = true;
		bullet->moveFoward(10);
		bullet->setRotation(bullet->rotation() + 1);
	} else
		bullet->cleanup = true;
};

EntityAI<Enemy> AI::enemy1 = [](Enemy* enemy) {
//	if (enemy->time % 10 == 0) {
//		bulletCircle(enemy, Textures::enemyBullet2, enemy->pos(),
//								 AI::enemyBullet1, enemy->time, 16);
//	}
//	foreach (CollidableEntity* entity, enemy->getValidHits()) {
//		enemy->decHealth();
//		entity->cleanup = true;
//	}
//	if (enemy->getHealth() == 0)
//		enemy->cleanup = true;
};
