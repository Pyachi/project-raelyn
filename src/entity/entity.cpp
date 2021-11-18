#include "entity.h"
#include "entitybullet.h"
#include "game.h"

Entity::Entity(EntityType type, const Texture& tex)
    : Entity(type, tex, UID()) {}

Entity::Entity(EntityType type, const Texture& tex, const UID& id)
    : QGraphicsPixmapItem(tex, &Game::getPlayableArea()),
      type(type),
      id(id),
      age(0),
      cleanup(false),
      movementTicks(0) {
  Game::addEntity(this);
  setZValue(tex.zValue);
  setOffset(-boundingRect().center());
}

void Entity::handleMovement() {
	if (movementTicks != 0) {
		switch (movementType) {
			case SMOOTH:
				moveTowardsPoint(targetPos,
												 QVector2D(targetPos - pos()).length() / movementTicks);
				movementTicks--;
				break;
			case QUICK:
				moveTowardsPoint(targetPos, QVector2D(targetPos - pos()).length() / 20);
				movementTicks--;
				break;
		}
	}
}
//***************************************************************************
void Entity::moveForward(double distance) {
  double rot = qDegreesToRadians(rotation());
  double dx = distance * -sin(rot);
  double dy = distance * cos(rot);

  moveBy(dx, dy);
}

void Entity::moveTowardsPoint(const QPointF& point, double distance) {
  QVector2D dir = QVector2D(point - pos()).normalized() * distance;
  moveBy(dir.x(), dir.y());
}

void Entity::moveTo(const QPointF& loc, int time, MovementType type) {
	targetPos = loc;
	movementTicks = type == SMOOTH ? time : 500;
	movementType = type;
}
//***************************************************************************
List<EntityBullet*> Entity::fireBullets(const List<BulletInfo>& list,
                                        double rot,
																				const QPointF& loc,
																				bool collision) {
  List<EntityBullet*> bullets;
  for (const BulletInfo& info : list) {
    for (const SpawnInfo& spawnInfo : info.info) {
			EntityBullet* bullet =
					new EntityBullet(info.tex, info.ai, this, info.damage);
      bullet->setPos(pos() + loc + spawnInfo.loc);
      bullet->setRotation(rotation() + rot + spawnInfo.rot);
      bullet->setScale(info.scale);
			bullet->collisionCheck = collision;
      bullets.push_back(bullet);
    }
  }
  return bullets;
}
//***************************************************************************
Entity* Entity::getNearestEntity(EntityType type) const {
	Entity* closest = nullptr;
	double closestDistance = 99999999;
	for (auto entity : Game::getEntities()) {
		if (entity.second->type == type &&
				entity.second->distanceSquared(this) < closestDistance) {
			closest = entity.second;
			closestDistance = entity.second->distanceSquared(this);
		}
	}
	return closest;
}

List<Entity*> Entity::getCollisions(EntityType type) const {
	List<Entity*> list;
	for (QGraphicsItem* item : collidingItems()) {
		if (Entity* entity = dynamic_cast<Entity*>(item))
			if (entity->type == type)
				list.push_back(entity);
	}
	return list;
}

List<Entity*> Entity::getNearbyEntities(EntityType type,
																				double distance) const {
	List<Entity*> list;
	for (auto pair : Game::getEntities()) {
		Entity* entity = pair.second;
		if (entity->type == type && distanceSquared(entity) <= distance * distance)
			list.push_back(entity);
	}
	return list;
}

double Entity::getDirectionOfEntity(const Entity* entity) const {
	if (entity == nullptr)
		return 0;
	QVector2D vec = QVector2D(entity->pos() - pos()).normalized();
	return qRadiansToDegrees(qAcos(vec.y())) * ((vec.x() > 0 ? -1 : 1));
}
//***************************************************************************
double Entity::distanceSquared(const Entity* entity) const {
  return pow(pos().x() - entity->pos().x(), 2) +
         pow(pos().y() - entity->pos().y(), 2);
}

QPointF Entity::confineToPlayableArea(const QPointF& pos) const {
  return QPointF(qBound(Game::getPlayableArea().boundingRect().left() -
                            boundingRect().left(),
                        pos.x(),
                        Game::getPlayableArea().boundingRect().right() -
                            boundingRect().right()),
                 qBound(Game::getPlayableArea().boundingRect().top() -
                            boundingRect().top(),
                        pos.y(),
                        Game::getPlayableArea().boundingRect().bottom() -
                            boundingRect().bottom()));
}

bool Entity::isOnScreen(void) const {
  return collidesWithItem(&Game::getPlayableArea());
}
//***************************************************************************
