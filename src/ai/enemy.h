#ifndef ENEMIES_H
#define ENEMIES_H

#include <QPointF>

enum Enemy { ENEMYTEST };

class EntityEnemy;
class UUID;

namespace Enemies {
extern EntityEnemy* spawn(Enemy, UUID, const QPointF&);
}

#endif  // ENEMIES_H
