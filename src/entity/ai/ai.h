#ifndef AI_H
#define AI_H

#include <functional>
#include "src/entity/entities/bullet.h"
#include "src/entity/entities/enemy.h"
#include "src/entity/entities/player.h"

namespace AI {
extern std::function<void(Bullet*)> playerBullet;
extern std::function<void(Bullet*)> enemyBullet1;
extern std::function<void(Bullet*)> enemyBullet2;
extern std::function<void(Bullet*)> enemyBulletSpiral;
extern std::function<void(Enemy*)> enemy;
}  // namespace AI

#endif  // AI_H
