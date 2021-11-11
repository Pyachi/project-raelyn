#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include <QPointF>

enum Collectable {
  COLLECTABLE_POWER,
  COLLECTABLE_POINTS,
  COLLECTABLE_HEALTH,
  COLLECTABLE_BOMB
};

class EntityCollectable;

namespace Collectables {
extern EntityCollectable* spawn(Collectable, const QPointF&);
}

#endif  // COLLECTABLES_H
