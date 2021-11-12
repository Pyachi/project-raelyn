#ifndef ENEMIES_H
#define ENEMIES_H

#include "util.h"

enum Enemy {
  ENEMY_ENEMYTEST1,  // ADD NEW ENEMIES HERE
  ENEMY_ENEMYTEST2,
  ENEMY_SIMPLESHOTGUN_TOP_LEFT,
  ENEMY_SIMPLESHOTGUN_TOP_RIGHT,
  ENEMY_TANKYBANG_UP_DOWN,
  ENEMY_SIMPLESHOTGUN_MID_LEFT_UP,
  ENEMY_SIMPLESHOTGUN_MID_RIGHT_UP,
  ENEMY_WAVE1BASIC,
};

class EntityEnemy;
class UID;

namespace Enemies {
extern EntityEnemy* spawn(Enemy enemy, UID id, const QPointF& loc);
}

#endif  // ENEMIES_H
