#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include <QPointF>

enum Collectable { POWER, POINTS, HEALTH, BOMB };

class EntityCollectable;

namespace Collectables {
extern EntityCollectable* spawn(Collectable, const QPointF&);
}

#endif  // COLLECTABLES_H
