#ifndef AI_H
#define AI_H

#include <functional>

class PlayerHitbox;
class Player;
class Enemy;
class Bullet;

template <class T>
using EntityAI = std::function<void(T*)>;

namespace AI {
extern EntityAI<PlayerHitbox> playerHitbox;
extern EntityAI<Player> player1;
extern EntityAI<Enemy> enemy1;
extern EntityAI<Bullet> playerBullet1;
extern EntityAI<Bullet> enemyBullet1;
};  // namespace AI

#endif  // AI_H
