#include "enemy.h"
#include "bulletpattern.h"
#include "src/entity/entityenemy.h"
#include "src/framework/game.h"

namespace Enemies {
EntityEnemy* spawn(Enemy enemy, UUID uuid, const QPointF& loc) {
  EntityEnemy* entity;
  switch (enemy) {
    // new EntityEnemy(TEXTURE, 'uuid', HEALTH, AI);
    case ENEMY_ENEMYTEST1:
      entity = new EntityEnemy(TEXENEMY1, uuid, 50, [](EntityEnemy* enemy) {
        if (enemy->cycle(50))
          enemy->fireBullets(PATTERN_SHOTGUN10X5);
      });
      break;
    //***********************************************************************************
    case ENEMY_ENEMYTEST2:
      entity = new EntityEnemy(TEXENEMY1, uuid, 100, [](EntityEnemy* enemy) {
        if (enemy->getAge() < 60)

          enemy->moveBy(0, 1);
        if (enemy->getAge() == 60)
          enemy->deleteLater();
      });
      break;
    //************************************************************************************
    case ENEMY_SIMPLESHOTGUN_TOP_LEFT:
      entity = new EntityEnemy(TEXENEMY1, uuid, 5, [](EntityEnemy* enemy) {
        if (enemy->cycle(1800, 1, 150))
          enemy->moveBy(2, 2);
        else if (enemy->cycle(1800, 151, 250))
          enemy->moveBy(1, 0);
        else if (enemy->cycle(1800, 251, 800))
          enemy->moveBy(1, -1);

        if (enemy->cycle(1800, 200))
          enemy->fireBullets(PATTERN_SHOTGUN8X3);

        if (enemy->getAge() == 930)  // 15 seconds plus off screen
          enemy->deleteLater();
      });
      break;
    //************************************************************************************
    case ENEMY_SIMPLESHOTGUN_TOP_RIGHT:
      entity = new EntityEnemy(TEXENEMY1, uuid, 15, [](EntityEnemy* enemy) {
        if (enemy->cycle(1800, 1, 150))
          enemy->moveBy(-2, -2);
        else if (enemy->cycle(1800, 151, 250))
          enemy->moveBy(-1, 0);
        else if (enemy->cycle(1800, 251, 800))
          enemy->moveBy(-1, 1);

        if (enemy->cycle(1800, 200))
          enemy->fireBullets(PATTERN_SHOTGUN8X3);

        if (enemy->getAge() == 930)  // 15 seconds plus off screen
          enemy->deleteLater();
      });
      break;
    //***************************************************************************************
    case ENEMY_TANKYSHOTGUN_UP_DOWN:
      entity = new EntityEnemy(TEXENEMY1, uuid, 100, [](EntityEnemy* enemy) {
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
          enemy->fireBullets(PATTERN_SHOTGUN8X5);

        if (enemy->getAge() == 1900)  // 15 seconds plus off screen
          enemy->deleteLater();
      });
      break;
    //****************************************************************************************
    case ENEMY_SIMPLESHOTGUN_MID_LEFT_UP:
      entity = new EntityEnemy(TEXENEMY1, uuid, 15, [](EntityEnemy* enemy) {
        if (enemy->cycle(1800, 1, 120))
          enemy->moveBy(2.5, 0);
        if (enemy->cycle(1800, 160, 240))
          enemy->moveBy(0, -2);
        if (enemy->cycle(1800, 280, 900))
          enemy->moveBy(-2.75, -2.75);

        if (enemy->getAge() == 159) {
          enemy->fireBullets(PATTERN_SHOTGUN8X3, 180);
          enemy->fireBullets(PATTERN_SHOTGUN8X3);
        }
        if (enemy->getAge() == 279)
          enemy->fireBullets(PATTERN_SHOTGUN8X3);

        if (enemy->getAge() == 900)  // 15 seconds plus off screen
          enemy->deleteLater();
      });
      break;
    //***************************************************************************************
    case ENEMY_SIMPLESHOTGUN_MID_RIGHT_UP:
      entity = new EntityEnemy(TEXENEMY1, uuid, 15, [](EntityEnemy* enemy) {
        if (enemy->cycle(1800, 1, 120))
          enemy->moveBy(-2.5, 0);
        if (enemy->cycle(1800, 130, 240))
          enemy->moveBy(2.5, 0);
        if (enemy->cycle(1800, 250, 900))
          enemy->moveBy(2.75, -2.75);

        if (enemy->getAge() == 125)
          enemy->fireBullets(PATTERN_SHOTGUN8X3);
        if (enemy->getAge() == 245)
          enemy->fireBullets(PATTERN_SHOTGUN8X3);

        if (enemy->getAge() == 900)  // 15 seconds plus off screen
          enemy->deleteLater();
      });
      break;
    //***************************************************************************************
    case ENEMY_WAVE1BASIC:
      entity = new EntityEnemy(TEXENEMY1, uuid, 25, [](EntityEnemy* enemy) {
        if (enemy->cycle(240, 0, 100))
          enemy->moveBy(1, 2);
        else if (enemy->cycle(240, 140, 240))
          enemy->moveBy(1, -2);
        if (enemy->getAge() == 240)
          enemy->deleteLater();
        if (enemy->getAge() == 120)
          enemy->fireBullets(PATTERN_SHOTGUN8X3);
      });
      break;
  }
  entity->setPos(loc);
  return entity;
}
}  // namespace Enemies
