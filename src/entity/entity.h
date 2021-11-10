#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "util.h"
#include "src/ai/bulletpattern.h"
#include "src/assets/texture.h"
#include "src/network/uuid.h"

class EntityBullet;

enum EntityType { ENEMY, BULLET, PLAYER, ONLINEPLAYER, HITBOX, COLLECTABLE };

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(EntityType, Tex);
	Entity(EntityType, Tex, UUID);

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
	List<EntityBullet*> fireBullets(Pattern, double = 0, const QPointF& = {0, 0});
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
