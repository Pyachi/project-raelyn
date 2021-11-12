#include "entity.h"
#include "Framework"
#include "AI"

Entity::Entity(EntityType type, Texture tex) : Entity(type, tex, UID()) {}

Entity::Entity(EntityType type, Texture tex, UID id)
		: QGraphicsPixmapItem(Textures::getTexture(tex), &Game::getPlayableArea()),
			type(type),
			id(id),
			age(0),
			cleanup(false),
			movementTicks(0) {
	Game::addEntity(this);
	setZValue(Textures::getZValue(tex));
	setOffset(-boundingRect().center());
}

void Entity::deleteLater() { cleanup = true; }

int Entity::getAge() { return age; }

bool Entity::readyToDelete() { return cleanup; }

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

void Entity::rotate(double deg) { setRotation(rotation() + deg); }

List<EntityBullet*> Entity::fireBullets(Pattern pattern,
																				BulletAI ai,
																				Texture texture,
																				double rot,
																				const QPointF& loc,
																				int scale,
																				int damage) {
	return fireBullets(
			Patterns::get(pattern), ai, texture, rot, loc, scale, damage);
}

List<EntityBullet*> Entity::fireBullets(List<BulletInfo> pattern,
																				BulletAI ai,
																				Texture texture,
																				double rot,
																				const QPointF& loc,
																				int scale,
																				int damage) {
	List<EntityBullet*> list;
	for (BulletInfo info : pattern)
		list.push_back(fireBullet(info, ai, texture, rot, loc, scale, damage));
	return list;
}

EntityBullet* Entity::fireBullet(BulletInfo info,
																 BulletAI ai,
																 Texture tex,
																 double rot,
																 const QPointF& loc,
																 int scale,
																 int damage) {
	return Bullets::spawn(ai, info, tex, this, rot, loc, scale, damage);
}

double Entity::distanceSquared(const Entity* entity) {
	return pow(pos().x() - entity->pos().x(), 2) +
				 pow(pos().y() - entity->pos().y(), 2);
}

double Entity::getDirectionOfEntity(const Entity* entity) {
	if (entity == nullptr)
		return 0;
	QVector2D vec = QVector2D(entity->pos() - pos()).normalized();
	return qRadiansToDegrees(qAcos(vec.y())) * ((vec.x() > 0 ? -1 : 1));
}

QPointF Entity::confineToPlayableArea(const QPointF& pos) {
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

bool Entity::isOnScreen(void) {
	return collidesWithItem(&Game::getPlayableArea());
}

bool Entity::cycle(int dur) { return cycle(dur, 0, 0); }

bool Entity::cycle(int dur, int time) { return cycle(dur, time, time); }

bool Entity::cycle(int dur, int low, int high) {
	return (getAge() % dur >= low && getAge() % dur <= high);
}

Entity* Entity::getNearestEntity(EntityType type) {
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

List<Entity*> Entity::getCollisions(EntityType type) {
	List<Entity*> list;
	for (QGraphicsItem* item : collidingItems()) {
		if (Entity* entity = dynamic_cast<Entity*>(item))
			if (entity->type == type)
				list.push_back(entity);
	}
	return list;
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

void Entity::moveTo(const QPointF& loc, int time, MovementType type) {
	targetPos = loc;
	movementTicks = time;
	movementType = type;
}
