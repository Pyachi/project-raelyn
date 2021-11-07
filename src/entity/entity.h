#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "alias.h"
#include "src/game.h"

class Texture;
class Bullet;
struct BulletInfo;

enum EntityType {
	ENEMY,
	BULLET,
	PLAYER,
	PLAYERHITBOX,
	COLLECTABLE
};

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(EntityType, const Texture&);

	void deleteLater();
	int getAge();
	bool readyToDelete();

	void moveFoward(double);
	void moveTowardsPoint(const QPointF&, double);
	void rotate(double);

	List<Bullet*> fireBullets(const List<BulletInfo>&,
														double = 0,
														const QPointF& = QPointF(0, 0));

	double distanceSquared(const Entity&);
	QPointF confineToPlayableArea(const QPointF&);
	bool isOnScreen();

	bool cycle(int);
	bool cycle(int, int);
	bool cycle(int, int, int);

	Entity* getNearestEntity(EntityType);

	List<Entity*> getCollisions(EntityType);

	virtual void tick() = 0;

	const EntityType type;

 protected:
	int age;
	bool cleanup;
};

#endif  // ENTITYTYPES_H
