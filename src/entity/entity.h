#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "texture.h"
#include "uid.h"
#include "pattern.h"
#include "bullet.h"

class EntityBullet;

enum EntityType {
	ENEMY,
	BULLET,
	PLAYER,
	ONLINEPLAYER,
	COLLECTABLE
};

enum MovementType {
	SMOOTH,
	QUICK
};

class Entity : public QGraphicsPixmapItem {
 public:
	Entity(EntityType type, Texture tex);
	Entity(EntityType type, Texture tex, UID id);

	void deleteLater(void);
	int getAge(void);
	bool readyToDelete(void);

	virtual void tick(void) = 0;

	const EntityType type;
	const UID id;

 protected:
	int age;
	bool cleanup;
	QPointF targetPos;
	int movementTicks;
	MovementType movementType;
	void handleMovement(void);

 public:
	// Utility Functions
	void moveForward(double dis);
	void moveTowardsPoint(const QPointF& loc, double dis);
	void moveTo(const QPointF& loc, int time, MovementType type = SMOOTH);
	void rotate(double rot);
	List<EntityBullet*> fireBullets(Pattern pat,
																	BulletAI ai,
																	Texture tex,
																	double rot = 0,
																	const QPointF& loc = {0, 0},
																	int scale = 1,
																	int damage = 1);
	List<EntityBullet*> fireBullets(List<BulletInfo> list,
																	BulletAI ai,
																	Texture tex,
																	double rot = 0,
																	const QPointF& loc = {0, 0},
																	int scale = 1,
																	int damage = 1);
	EntityBullet* fireBullet(BulletInfo info,
													 BulletAI ai,
													 Texture tex,
													 double rot = 0,
													 const QPointF& loc = {0, 0},
													 int scale = 1,
													 int damage = 1);
	Entity* getNearestEntity(EntityType type);
	List<Entity*> getCollisions(EntityType type);
	List<Entity*> getNearbyEntities(EntityType type, double distance);
	double getDirectionOfEntity(const Entity* entity);
	double distanceSquared(const Entity* entity);
	QPointF confineToPlayableArea(const QPointF& loc);
	bool isOnScreen(void);
	bool cycle(int dur);
	bool cycle(int dur, int time);
	bool cycle(int dur, int low, int high);
};

#endif  // ENTITYTYPES_H
