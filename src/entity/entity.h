#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "alias.h"
#include "src/network/uuid.h"

class Texture;
class Bullet;
struct BulletInfo;

enum EntityType {
	ENEMY,
	BULLET,
	PLAYER,
	ONLINEPLAYER,
	PLAYERHITBOX,
	COLLECTABLE
};

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(EntityType, const Texture&);
	Entity(EntityType, const Texture&, UUID);

	void deleteLater();
	int getAge();
	bool readyToDelete();

	virtual void tick() = 0;

	const EntityType type;
	const UUID id;

 protected:
	int age;
	bool cleanup;

 public:
	// Utility Functions
	void moveFoward(double);
	void moveTowardsPoint(const QPointF&, double);
	void rotate(double);
	List<Bullet*> fireBullets(const List<BulletInfo>&,
														double = 0,
														const QPointF& = QPointF(0, 0));
	Entity* getNearestEntity(EntityType);
	List<Entity*> getCollisions(EntityType);
	double distanceSquared(const Entity&);
	QPointF confineToPlayableArea(const QPointF&);
	bool isOnScreen();
	bool cycle(int);
	bool cycle(int, int);
	bool cycle(int, int, int);
};

#endif  // ENTITYTYPES_H
