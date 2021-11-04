#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "src/game.h"

class Texture;
class Bullet;
class Bullets;

template <class T>
using EntityAI = std::function<void(T*)>;

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(const Texture&, const QPointF&);

	bool cleanup;
	int timeAlive;

	void moveFoward(const double&);
	void moveTowardsPoint(const QPointF&, const double&);
	void rotate(const double&);

	Bullet* fireBullet(const Bullets&, const QPointF&, const double& = 0);
	QList<Bullet*> fireBulletCircle(const Bullets&,
																	const QPointF&,
																	const int&,
																	const double& = 0);
	template <class T>
	T* getNearestEntity();

	template <class T>
	QList<T*> getCollisions();

	double distanceSquared(Entity*);

	QPointF confineToPlayableArea(const QPointF&);
	bool isOnScreen();

	bool cycle(const int&);
	bool cycle(const int&, const int&);
	bool cycle(const int&, const int&, const int&);

	virtual void tick() = 0;
};

template <class T>
T* Entity::getNearestEntity() {
	T* closest = nullptr;
	double closestDis = 99999999;
	foreach(Entity * baseEntity, Game::GAME->getEntities()) {
		if (T* entity = dynamic_cast<T*>(baseEntity)) {
			double distance = distanceSquared(entity);
			if (distance < closestDis) {
				closest = entity;
				closestDis = distance;
			}
		}
	}
	return closest;
}

template <class T>
QList<T*> Entity::getCollisions() {
	QList<T*> list;
	foreach(QGraphicsItem * item, collidingItems()) {
		if (T* entity = dynamic_cast<T*>(item))
			list.append(entity);
	}
	return list;
}

#endif  // ENTITYTYPES_H
