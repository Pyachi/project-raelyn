#include "entity.h"
#include <QVector2D>
#include <QtMath>
#include "entitybullet.h"
#include "src/ai/bullet.h"
#include "src/ai/bulletpattern.h"
#include "src/assets/texture.h"
#include "src/framework/game.h"

Entity::Entity(EntityType type, Texture tex) : Entity(type, tex, UID()) {}

Entity::Entity(EntityType type, Texture tex, UID id)
		: QGraphicsPixmapItem(&Game::getPlayableArea()),
			type(type),
			id(id),
			age(0),
			cleanup(false) {
	setPixmap(QPixmap(QString::fromStdString(Textures::getTexture(tex))));
	setZValue(Textures::getZValue(tex));
	setOffset(-boundingRect().center());
}

void Entity::deleteLater() { cleanup = true; }

int Entity::getAge() { return age; }

bool Entity::readyToDelete() { return cleanup; }

void Entity::moveFoward(double distance) {
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
																				Texture texture,
																				double rot,
																				const QPointF& loc,
																				int damage) {
	List<EntityBullet*> list;
	for (BulletInfo info : Patterns::get(pattern))
		list.push_back(info.spawn(texture, this, rot, loc, damage));
	return list;
}

double Entity::distanceSquared(const Entity& entity) {
	return pow(pos().x() - entity.pos().x(), 2) +
				 pow(pos().y() - entity.pos().y(), 2);
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
				entity.second->distanceSquared(*this) < closestDistance) {
			closest = entity.second;
			closestDistance = entity.second->distanceSquared(*this);
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
