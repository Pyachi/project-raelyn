#include "boss.h"
#include "Assets"
#include "Entity"
#include "AI"
#include "Framework"

namespace Bosses {
EntityBoss* spawn(Boss boss, UID uuid, const QPointF& loc) {
	EntityBoss* entity;
	switch (boss) {
		//******************************************************************************************
		case BOSS_LVL1MINI:
			entity =
					new EntityBoss(TEXTURE_ENEMYTEMP, uuid, 200, 3, [](EntityBoss* boss) {
						switch (boss->phase) {
							case 3:
								if (boss->cycle(1000, 10) || boss->cycle(1000, 510))
									boss->moveTo({0, -200}, 100, QUICK);
								if (boss->cycle(1000, 260))
									boss->moveTo({-200, -200}, 100, QUICK);
								if (boss->cycle(1000, 760))
									boss->moveTo({200, -200}, 100, QUICK);
								if (boss->cycle(250, 100) || boss->cycle(250, 150) ||
										boss->cycle(250, 200)) {
									boss->fireBullets(
											BulletInfo(-10) << BulletInfo(10) << BulletInfo(),
											AI_BASIC4,
											TEXTURE_BULLET_ROUND_BLUE,
											boss->getDirectionOfEntity(Game::getPlayer()),
											{0, 0},
											2);
									boss->fireBullets(
											BulletInfo(-5) << BulletInfo(5),
											AI_BASIC5,
											TEXTURE_BULLET_ROUND_BLUE,
											boss->getDirectionOfEntity(Game::getPlayer()),
											{0, 0},
											2);
									boss->fireBullets(
											BulletInfo(-10) << BulletInfo(10) << BulletInfo(),
											AI_BASIC6,
											TEXTURE_BULLET_ROUND_BLUE,
											boss->getDirectionOfEntity(Game::getPlayer()),
											{0, 0},
											2);
									boss->fireBullets(
											BulletInfo(-5) << BulletInfo(5),
											AI_BASIC7,
											TEXTURE_BULLET_ROUND_BLUE,
											boss->getDirectionOfEntity(Game::getPlayer()),
											{0, 0},
											2);
									boss->fireBullets(
											BulletInfo(-10) << BulletInfo(10) << BulletInfo(),
											AI_BASIC8,
											TEXTURE_BULLET_ROUND_BLUE,
											boss->getDirectionOfEntity(Game::getPlayer()),
											{0, 0},
											2);
								}
								break;
							case 2:

								break;
							case 1:

								break;
						}
					});
			break;
		//******************************************************************************************
		case BOSS_LVL1:
			entity = new EntityBoss(
					TEXTURE_ENEMYTEMP, uuid, 200, 5, [](EntityBoss* boss) {});
			break;
		//******************************************************************************************
		case BOSS_LVL2MINI:
			entity = new EntityBoss(
					TEXTURE_ENEMYTEMP, uuid, 200, 5, [](EntityBoss* boss) {});
			break;
		//******************************************************************************************
		case BOSS_LVL2:
			entity = new EntityBoss(
					TEXTURE_ENEMYTEMP, uuid, 200, 5, [](EntityBoss* boss) {});
			break;
		//******************************************************************************************
		case BOSS_LVL3MINI:
			entity = new EntityBoss(
					TEXTURE_ENEMYTEMP, uuid, 200, 5, [](EntityBoss* boss) {});
			break;
		//******************************************************************************************
		case BOSS_LVL3:
			entity = new EntityBoss(
					TEXTURE_ENEMYTEMP, uuid, 200, 5, [](EntityBoss* boss) {});
			break;
			//******************************************************************************************
	}
	entity->setPos(loc);
	return entity;
}
}
