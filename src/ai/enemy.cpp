#include "enemy.h"
#include "bulletpattern.h"
#include "src/entity/entityenemy.h"
#include "src/framework/game.h"

namespace Enemies {
EntityEnemy* spawn(Enemy enemy, UID uuid, const QPointF& loc) {
  EntityEnemy* entity;
  switch (enemy) {
    // new EntityEnemy(TEXTURE, 'uuid', HEALTH, AI);
    case ENEMY_ENEMYTEST1:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 50, [](EntityEnemy* enemy) {
						if (enemy->cycle(50))
							enemy->fireBullets(PATTERN_SHOTGUN10X5,
																 TEXTURE_BULLET_ROUND_AQUA);
					});
      break;
    //***********************************************************************************
    case ENEMY_ENEMYTEST2:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 100, [](EntityEnemy* enemy) {
						if (enemy->getAge() < 60)

							enemy->moveBy(0, 1);
						if (enemy->getAge() == 60)
							enemy->deleteLater();
					});
      break;
    //************************************************************************************
    case ENEMY_SIMPLESHOTGUN_TOP_LEFT:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 5, [](EntityEnemy* enemy) {
						if (enemy->cycle(1800, 1, 150))
							enemy->moveBy(2, 2);
						else if (enemy->cycle(1800, 181, 240))
							enemy->moveBy(1, 0);
						else if (enemy->cycle(1800, 271, 800))
							enemy->moveBy(0, -1);

						if (enemy->getAge() == 180)
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);
						if (enemy->getAge() == 270)
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);

						if (enemy->getAge() == 930)  // 15 seconds plus off screen
							enemy->deleteLater();
					});
      break;
    //************************************************************************************
    case ENEMY_SIMPLESHOTGUN_TOP_RIGHT:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 15, [](EntityEnemy* enemy) {
						if (enemy->cycle(1800, 1, 150))
							enemy->moveBy(-2, 2);
						else if (enemy->cycle(1800, 181, 240))
							enemy->moveBy(-1, 0);
						else if (enemy->cycle(1800, 271, 800))
							enemy->moveBy(0, -1);

						if (enemy->getAge() == 180)
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);
						if (enemy->getAge() == 270)
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);
						if (enemy->getAge() == 930)  // 15 seconds plus off screen
							enemy->deleteLater();
					});
      break;
    //***************************************************************************************
    case ENEMY_TANKYSHOTGUN_UP_DOWN:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 100, [](EntityEnemy* enemy) {
						if (enemy->cycle(1800, 1, 175))
							enemy->moveBy(0, 1.75);
						if (enemy->cycle(1800, 176, 350))
							enemy->moveBy(0, -1);
						if (enemy->cycle(1800, 351, 525))
							enemy->moveBy(0, 1);
						if (enemy->cycle(1800, 526, 700))
							enemy->moveBy(0, -1);
						if (enemy->cycle(1800, 701, 875))
							enemy->moveBy(0, 1);
						if (enemy->cycle(1800, 876, 1050))
							enemy->moveBy(0, -1);
						if (enemy->cycle(1800, 1051, 1800))
							enemy->moveBy(0, -3);

						if (enemy->cycle(350, 175))
							enemy->fireBullets(PATTERN_TRIPLESHOTGUNX3,
																 TEXTURE_BULLET_ROUND_AQUA);

						if (enemy->getAge() == 1900)  // 15 seconds plus off screen
							enemy->deleteLater();
					});
      break;
    //****************************************************************************************
    case ENEMY_SIMPLESHOTGUN_MID_LEFT_UP:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 40, [](EntityEnemy* enemy) {
						if (enemy->cycle(1800, 1, 120))
							enemy->moveBy(5, 0);
						if (enemy->cycle(1800, 160, 240))
							enemy->moveBy(0, -2);
						if (enemy->cycle(1800, 280, 900))
							enemy->moveBy(-2.75, -2.75);

						if (enemy->getAge() == 155) {
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);
						}
						if (enemy->getAge() == 275)
							enemy->fireBullets(PATTERN_SHOTGUN8X5, TEXTURE_BULLET_ROUND_AQUA);

						if (enemy->getAge() == 900)  // 15 seconds plus off screen
							enemy->deleteLater();
					});
      break;
    //***************************************************************************************
    case ENEMY_SIMPLESHOTGUN_MID_RIGHT_UP:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 40, [](EntityEnemy* enemy) {
						if (enemy->cycle(1800, 1, 120))
							enemy->moveBy(-5, 0);
						if (enemy->cycle(1800, 160, 240))
							enemy->moveBy(0, -2);
						if (enemy->cycle(1800, 280, 900))
							enemy->moveBy(2.75, -2.75);

						if (enemy->getAge() == 155)
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);
						if (enemy->getAge() == 275)
							enemy->fireBullets(PATTERN_SHOTGUN8X5, TEXTURE_BULLET_ROUND_AQUA);

						if (enemy->getAge() == 900)  // 15 seconds plus off screen
							enemy->deleteLater();
					});
      break;
    //***************************************************************************************
    case ENEMY_WAVE1BASIC:
			entity =
					new EntityEnemy(TEXTURE_ENEMYTEMP, uuid, 25, [](EntityEnemy* enemy) {
						if (enemy->cycle(240, 0, 100))
							enemy->moveBy(1, 2);
						else if (enemy->cycle(240, 140, 240))
							enemy->moveBy(1, -2);
						if (enemy->getAge() == 240)
							enemy->deleteLater();
						if (enemy->getAge() == 120)
							enemy->fireBullets(PATTERN_SHOTGUN8X3, TEXTURE_BULLET_ROUND_AQUA);
					});
      break;
  }
  entity->setPos(loc);
  return entity;
}
}  // namespace Enemies
