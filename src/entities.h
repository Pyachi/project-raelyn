#ifndef ENTITIES_H
#define ENTITIES_H

template <class T>
struct EntityInfo;

class Player;
class Enemy;
class Bullet;

using PlayerInfo = EntityInfo<Player>;
using EnemyInfo = EntityInfo<Enemy>;
using BulletInfo = EntityInfo<Bullet>;

namespace Players {
extern const PlayerInfo PLAYER1;
extern const PlayerInfo PLAYER2;
}

namespace Enemies {
extern const EnemyInfo ENEMY1;
extern const EnemyInfo ENEMY2;
}

namespace Bullets {
extern const BulletInfo PLAYERBASIC;
extern const BulletInfo PLAYERHOMING;
extern const BulletInfo SPIRALCW;
extern const BulletInfo SPIRALCCW;
extern const BulletInfo FLOWERCW;
extern const BulletInfo FLOWERCCW;
extern const BulletInfo ACCELERATING;
}

#endif  // ENTITIES_H
