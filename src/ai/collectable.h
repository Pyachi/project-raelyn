#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include "util.h"

enum Collectable {
  COLLECTABLE_POWER,
  COLLECTABLE_POINTS,
  COLLECTABLE_HEALTH,
  COLLECTABLE_BOMB
};

class EntityCollectable;

namespace Collectables {
extern EntityCollectable* spawn(Collectable col,
																const QPointF& loc,
																bool random = true);
}

#endif  // COLLECTABLES_H
