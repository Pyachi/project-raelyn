#ifndef AI_H
#define AI_H

#include <functional>

class PlayerHitbox;
class Player;
class Enemy;
class Bullet;

template <class T>
using EntityAI = std::function<void(T*)>;

using PlayerAI = EntityAI<Player>;
using EnemyAI = EntityAI<Enemy>;
using BulletAI = EntityAI<Bullet>;

namespace AI {
extern PlayerAI player1;
extern EnemyAI enemy1;
extern EnemyAI enemy2;
};  // namespace AI

namespace BulletAI {
extern EntityAI<Bullet> playerBasic;
extern EntityAI<Bullet> playerHoming;
extern EntityAI<Bullet> spiralCW;
extern EntityAI<Bullet> spiralCCW;
extern EntityAI<Bullet> flowerCW;
extern EntityAI<Bullet> flowerCCW;
extern EntityAI<Bullet> accelerating;
}  // namespace BulletAI

#endif  // AI_H
