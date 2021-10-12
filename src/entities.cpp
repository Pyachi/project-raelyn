#include "entities.h"
#include "ai.h"
#include "entityinfo.h"
#include "textures.h"

PlayerInfo Players::player1 = PlayerInfo(Textures::player1, AI::player1);
EnemyInfo Enemies::enemy1 = EnemyInfo(Textures::enemy1, AI::enemy2, 500);

BulletInfo Bullets::playerBasic =
		BulletInfo(Textures::playerBasic, BulletAI::playerBasic, true);
BulletInfo Bullets::spiralCW =
		BulletInfo(Textures::bulletEllipse, BulletAI::spiralCW, true);
BulletInfo Bullets::spiralCCW =
		BulletInfo(Textures::bulletEllipse, BulletAI::spiralCCW, true);
BulletInfo Bullets::flowerCW =
		BulletInfo(Textures::bulletEllipse, BulletAI::flowerCW, false);
BulletInfo Bullets::flowerCCW =
		BulletInfo(Textures::bulletEllipse, BulletAI::flowerCCW, false);
