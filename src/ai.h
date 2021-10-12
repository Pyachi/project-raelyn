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
extern EntityAI<Enemy> enemy1;
extern EntityAI<Enemy> enemy2;
extern EntityAI<PlayerHitbox> playerHitbox;
extern EntityAI<Player> player1;
};  // namespace AI

namespace BulletAI {
extern EntityAI<Bullet> playerBasic;
extern EntityAI<Bullet> playerHoming;
extern EntityAI<Bullet> spiralCW;
extern EntityAI<Bullet> spiralCCW;
extern EntityAI<Bullet> flowerCW;
extern EntityAI<Bullet> flowerCCW;
}  // namespace BulletAI

#endif  // AI_H
