#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>

class Game;
class Texture;

template <class T>
using EntityAI = std::function<void(T*)>;

class BaseEntity : virtual public QGraphicsPixmapItem {
 public:
	BaseEntity(Game*, Texture*, QPointF);

	bool cleanup = false;

	bool isInsideBorder();
	void moveFoward(int);

 protected:
	Game* game;

	virtual void tick() = 0;
};

class LinkedEntity {
 public:
	LinkedEntity(BaseEntity*);

	BaseEntity* owner;
};

class CollidableEntity {
 public:
	CollidableEntity();

	QList<CollidableEntity*> getCollidingEntities();
};

template <class T>
class AIEntity {
 public:
	AIEntity(EntityAI<T>*);

	EntityAI<T> tick;
};

template <class T>
AIEntity<T>::AIEntity(EntityAI<T>* ai) {
	this->tick = *ai;
}

#endif  // ENTITYTYPES_H
