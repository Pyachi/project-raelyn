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
					new EntityBoss(TEXTURE_ENEMYTEMP, uuid, 50, 3, [](EntityBoss* boss) {
						switch (boss->phase) {
							case 3:
								if (boss->getAge() == 10)
									boss->moveTo({0, -200}, 100, QUICK);
								//						if
								//(boss->cycle(50))
								//							boss->fireBullets(
								//									BulletInfo(AI_BASIC4,
								//-5)
								//											<<
								//BulletInfo(AI_BASIC4, 5) << BulletInfo(AI_BASIC5, -5)
								//											<<
								//BulletInfo(AI_BASIC5, 5) << BulletInfo(AI_BASIC6, -5)
								//											<<
								//BulletInfo(AI_BASIC6, 5) << BulletInfo(AI_BASIC7, -5)
								//											<<
								//BulletInfo(AI_BASIC7, 5) << BulletInfo(AI_BASIC8, -5)
								//											<<
								//BulletInfo(AI_BASIC8, 5) << BulletInfo(AI_BASIC9, -5)
								//											<<
								//BulletInfo(AI_BASIC9, 5),
								//									TEXTURE_BULLET_ROUND_BLUE,
								//									boss->getDirectionOfEntity(Game::getPlayer()),
								//									{0,
								//0},
								//									2);
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
