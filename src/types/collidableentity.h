#ifndef COLLIDABLEENTITY_H
#define COLLIDABLEENTITY_H

#include <QList>

#include "baseentity.h"

class CollidableEntity : virtual public BaseEntity {
 public:
	CollidableEntity(Game*, Texture, QPoint);

	QList<CollidableEntity*> getCollidingEntities();
};

#endif  // COLLIDABLEENTITY_H
