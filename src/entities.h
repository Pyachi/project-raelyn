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
extern BulletInfo playerBasic;
extern BulletInfo spiralCW;
extern BulletInfo spiralCCW;
extern BulletInfo flowerCW;
extern BulletInfo flowerCCW;
}  // namespace Bullets

#endif  // ENTITIES_H
