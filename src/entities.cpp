#include "entities.h"
#include "ai.h"
#include "entityinfo.h"
#include "textures.h"

PlayerInfo Players::player1 = PlayerInfo(Textures::player1, AI::player1);
EnemyInfo Enemies::enemy1 = EnemyInfo(Textures::enemy1, AI::enemy1, 50);
BulletInfo Bullets::playerBullet1 =
		BulletInfo(Textures::playerBullet1, AI::playerBullet1, true);
BulletInfo Bullets::enemyBullet1 =
		BulletInfo(Textures::enemyBullet1, AI::enemyBullet1, false);
BulletInfo Bullets::enemyBullet2 =
		BulletInfo(Textures::enemyBullet2, AI::enemyBullet1, false);
