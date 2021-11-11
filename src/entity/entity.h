#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "util.h"
#include "src/ai/bulletpattern.h"
#include "src/assets/texture.h"
#include "src/network/uid.h"

class EntityBullet;

enum EntityType {
	ENEMY,
	BULLET,
	PLAYER,
	ONLINEPLAYER,
	HITBOX,
	COLLECTABLE
};

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(EntityType, Texture);
	Entity(EntityType, Texture, UID);

	void deleteLater(void);
	int getAge(void);
	bool readyToDelete(void);

	virtual void tick(void) = 0;

	const EntityType type;
	const UID id;

 protected:
	int age;
	bool cleanup;

 public:
	// Utility Functions
	void moveFoward(double);
	void moveTowardsPoint(const QPointF&, double);
	void rotate(double);
	List<EntityBullet*> fireBullets(Pattern,
																	Texture,
																	double = 0,
																	const QPointF& = {0, 0},
																	int = 1);
	Entity* getNearestEntity(EntityType);
	List<Entity*> getCollisions(EntityType);
	double distanceSquared(const Entity&);
	QPointF confineToPlayableArea(const QPointF&);
	bool isOnScreen(void);
	bool cycle(int);
	bool cycle(int, int);
	bool cycle(int, int, int);
};

#endif  // ENTITYTYPES_H
