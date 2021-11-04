#include "entity.h"
#include <QVector2D>
#include <QtMath>
#include "bullet.h"
#include "src/texture.h"

Entity::Entity(const Texture& texture, const QPointF& spawn)
		: QGraphicsPixmapItem(Game::getPlayableArea()),
			cleanup(false),
			timeAlive(0) {
	setPixmap(QPixmap(texture.texture));
	setZValue(texture.zValue);
	setOffset(-boundingRect().center());
	setPos(spawn);

	Game::addEntity(this);
}

void Entity::moveFoward(const double& distance) {
	double rot = qDegreesToRadians(rotation());
	double dx = distance * -sin(rot);
	double dy = distance * cos(rot);

	moveBy(dx, dy);
}

void Entity::moveTowardsPoint(const QPointF& point, const double& distance) {
	QVector2D dir(point - pos());
	dir.normalize();
	dir *= distance;
	moveBy(dir.x(), dir.y());
}

void Entity::rotate(const double& deg) { setRotation(rotation() + deg); }

Bullet* Entity::fireBullet(const Bullets& info,
													 const QPointF& spawn,
													 const double& rotation) {
	return new Bullet(info, this, pos() + spawn, rotation);
}

QList<Bullet*> Entity::fireBulletCircle(const Bullets& info,
																				const QPointF& spawn,
																				const int& count,
																				const double& startRotation) {
	QList<Bullet*> list;
	double rotation = startRotation;
	for (int i = 0; i < count; i++) {
		list.append(new Bullet(info, this, pos() + spawn, rotation));
		rotation += 360.0 / count;
	}
	return list;
}

QList<Bullet*> Entity::fireBulletArc(const Bullets& info,
																		 const QPointF& spawn,
																		 int count,
																		 double startRot,
																		 double endRot) {
	QList<Bullet*> list;
	double rotation = startRot;
	for (int i = 0; i < count; i++) {
		list.append(new Bullet(info, this, pos() + spawn, rotation));
		rotation += (endRot - startRot) / (count - 1);
	}
	return list;
}

double Entity::distanceSquared(Entity* entity) {
	return pow(pos().x() - entity->pos().x(), 2) +
				 pow(pos().y() - entity->pos().y(), 2);
}

QPointF Entity::confineToPlayableArea(const QPointF& pos) {
	return QPointF(qBound(Game::getPlayableArea()->boundingRect().left() -
														boundingRect().left(),
												pos.x(),
												Game::getPlayableArea()->boundingRect().right() -
														boundingRect().right()),
								 qBound(Game::getPlayableArea()->boundingRect().top() -
														boundingRect().top(),
												pos.y(),
												Game::getPlayableArea()->boundingRect().bottom() -
														boundingRect().bottom()));
}

bool Entity::isOnScreen() { return collidesWithItem(Game::getPlayableArea()); }

bool Entity::cycle(const int& dur) { return cycle(dur, 0, 0); }

bool Entity::cycle(const int& dur, const int& time) {
	return cycle(dur, time, time);
}

bool Entity::cycle(const int& dur, const int& low, const int& high) {
	return (timeAlive % dur >= low && timeAlive % dur <= high);
}
