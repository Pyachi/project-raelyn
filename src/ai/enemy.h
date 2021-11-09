#ifndef ENEMIES_H
#define ENEMIES_H

#include <QPointF>

enum Enemy {
	ENEMY_ENEMYTEST1,  // ADD NEW ENEMIES HERE
	ENEMY_ENEMYTEST2,
};

class EntityEnemy;
class UUID;

namespace Enemies {
extern EntityEnemy* spawn(Enemy, UUID, const QPointF&);
}

#endif  // ENEMIES_H
