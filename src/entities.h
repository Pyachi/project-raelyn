#ifndef ENTITIES_H
#define ENTITIES_H

struct PlayerInfo;
struct EnemyInfo;
struct BulletInfo;

namespace Players {
extern PlayerInfo player1;
}

namespace Enemies {
extern EnemyInfo enemy1;
}

namespace Bullets {
extern BulletInfo playerBullet1;
extern BulletInfo enemyBullet1;
extern BulletInfo enemyBullet2;
}  // namespace Bullets

#endif  // ENTITIES_H
