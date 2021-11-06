#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include "src/game/game.h"

class Texture;
class Bullet;
class BulletInfo;

using BulletList = std::vector<BulletInfo>;

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(const Texture&, const QPointF&);

	void deleteLater();
	int getAge();
	bool readyToDelete();

	QList<Bullet*> fireBullet(BulletList,
														double = 0,
														const QPointF& = QPointF(0, 0));
	QList<Bullet*> fireBulletCircle(BulletList,
																	int,
																	double = 0,
																	const QPointF& = QPointF(0, 0));
	QList<Bullet*> fireBulletArc(BulletList,
															 int,
															 double,
															 double,
															 const QPointF& = QPointF(0, 0));

	void moveFoward(double);
	void moveTowardsPoint(const QPointF&, double);
	void rotate(double);

	double distanceSquared(Entity*);
	QPointF confineToPlayableArea(const QPointF&);
	bool isOnScreen();

	bool cycle(int);
	bool cycle(int, int);
	bool cycle(int, int, int);

	template <class T>
	T* getNearestEntity();

	template <class T>
	QList<T*> getCollisions();

	virtual void tick() = 0;

 protected:
	int age;
	bool cleanup;
};

template <class T>
T* Entity::getNearestEntity() {
	T* closest = nullptr;
	double closestDis = 99999999;
	foreach(Entity * baseEntity, Game::getEntities()) {
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
