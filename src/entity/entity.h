#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include "bullet.h"
#include "texture.h"
#include "uid.h"

class EntityBullet;
struct BulletInfo;

enum EntityType { ENEMY, BULLET, PLAYER, ONLINEPLAYER, COLLECTABLE };

enum MovementType { SMOOTH, QUICK };

class Entity : public QGraphicsPixmapItem {
 public:
  Entity(EntityType type, const Texture& tex);
  Entity(EntityType type, const Texture& tex, const UID& id);

  void deleteLater(void);
  int getAge(void) const;
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
  //***************************************************************************
  void moveForward(double dis);
  void moveTowardsPoint(const QPointF& loc, double dis);
  void moveTo(const QPointF& loc, int time, MovementType type = SMOOTH);
  void rotate(double rot);
  //***************************************************************************
  List<EntityBullet*> fireBullets(const List<BulletInfo>& list,
                                  double rot = 0,
                                  const QPointF& loc = {0, 0});
  //***************************************************************************
  Entity* getNearestEntity(EntityType type) const;
  List<Entity*> getCollisions(EntityType type) const;
  List<Entity*> getNearbyEntities(EntityType type, double distance) const;
  double getDirectionOfEntity(const Entity* entity) const;
  double distanceSquared(const Entity* entity) const;
  QPointF confineToPlayableArea(const QPointF& loc) const;
  bool isOnScreen(void) const;
  bool cycle(int dur) const;
  bool cycle(int dur, int time) const;
  bool cycle(int dur, int low, int high) const;
};

#endif  // ENTITY_H
