#ifndef AI_H
#define AI_H

#include <functional>

class Bullet;
class Enemy;

template <class T>
using EntityAI = std::function<void(T*)>;

namespace AI {
extern EntityAI<Bullet> playerBullet1;
extern EntityAI<Bullet> enemyBullet1;
extern EntityAI<Enemy> enemy1;
}  // namespace AI

#endif  // AI_H
