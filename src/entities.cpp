#include "entities.h"
#include "ai.h"
#include "textures.h"
#include "entityinfo.h"

const PlayerInfo Players::PLAYER1 = PlayerInfo(Textures::player1, AI::player1);
const PlayerInfo Players::PLAYER2 = PlayerInfo(Textures::player1, AI::player1);

const EnemyInfo Enemies::ENEMY1 = EnemyInfo(Textures::enemy1, AI::enemy1);
const EnemyInfo Enemies::ENEMY2 = EnemyInfo(Textures::enemy1, AI::enemy2);

const BulletInfo Bullets::PLAYERBASIC = BulletInfo(Textures::playerBasic, BulletAI::)
