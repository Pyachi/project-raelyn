#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>

class Game;
class Texture;

class BaseEntity : virtual public QGraphicsPixmapItem {
 public:
	BaseEntity(Game*, Texture, QPoint);

	bool cleanup = false;
	int time = 0;

	bool isInsideBorder();
	void moveFoward(int);

 protected:
	Game* game;

	virtual void tick();
};

class LinkedEntity {
 public:
	LinkedEntity(BaseEntity*);

	BaseEntity* getOwner();

 protected:
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
	AIEntity(std::function<void(T*)>);

 protected:
	std::function<void(T*)> tick;
};

#endif  // ENTITYTYPES_H
