#include "collidableentity.h"
#include "linkedentity.h"

CollidableEntity::CollidableEntity(Game* game, Texture texture, QPoint spawn)
		: BaseEntity(game, texture, spawn) {}

QList<CollidableEntity*> CollidableEntity::getCollidingEntities() {
	QList<CollidableEntity*> list;
	foreach (QGraphicsItem* item, collidingItems()) {
		if (CollidableEntity* entity = dynamic_cast<CollidableEntity*>(item))
			list.append(entity);
	}
	return list;
}
