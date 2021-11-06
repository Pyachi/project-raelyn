#include "entity.h"
#include <QVector2D>
#include <QtMath>
#include "bullet.h"
#include "src/assets/texture.h"
#include "src/ai/bullettype.h"

Entity::Entity(const Texture& texture, const QPointF& spawn)
		: QGraphicsPixmapItem(Game::getPlayableArea()), age(0), cleanup(false) {
	setPixmap(QPixmap(texture.texture));
	setZValue(texture.zValue);
	setOffset(-boundingRect().center());
	setPos(spawn);
}

void Entity::deleteLater() { cleanup = true; }

int Entity::getAge() { return age; }

bool Entity::readyToDelete() { return cleanup; }

QList<Bullet*> Entity::fireBullet(BulletList pattern,
																	double rot,
																	const QPointF& loc) {
	QList<Bullet*> list;
	foreach(BulletInfo info, pattern) {
		list << info.spawn(this, pos() + loc, rot);
	}
	return list;
}

QList<Bullet*> Entity::fireBulletCircle(BulletList info,
																				int count,
																				double rot,
																				const QPointF& loc) {
	QList<Bullet*> list;
	for (int i = 0; i < count; i++) {
		list << fireBullet(info, rot, loc);
		rot += 360 / count;
	}
	return list;
}

QList<Bullet*> Entity::fireBulletArc(BulletList info,
																		 int count,
																		 double startRot,
																		 double endRot,
																		 const QPointF& loc) {
	QList<Bullet*> list;
	double rot = startRot;
	for (int i = 0; i < count; i++) {
		list << fireBullet(info, rot, loc);
		rot += (endRot - startRot) / (count - 1);
	}
	return list;
}

void Entity::moveFoward(double distance) {
	double rot = qDegreesToRadians(rotation());
	double dx = distance * -sin(rot);
	double dy = distance * cos(rot);

	moveBy(dx, dy);
}

void Entity::moveTowardsPoint(const QPointF& point, double distance) {
	QVector2D dir(point - pos());
	dir.normalize();
	dir *= distance;
	moveBy(dir.x(), dir.y());
}

void Entity::rotate(double deg) { setRotation(rotation() + deg); }

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

bool Entity::cycle(int dur) { return cycle(dur, 0, 0); }

bool Entity::cycle(int dur, int time) { return cycle(dur, time, time); }

bool Entity::cycle(int dur, int low, int high) {
	return (getAge() % dur >= low && getAge() % dur <= high);
}
