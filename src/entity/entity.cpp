#include "entity.h"
#include <QVector2D>
#include <QtMath>
#include "bullet.h"
#include "enemy.h"
#include "src/game.h"

BaseEntity::BaseEntity(const Texture& texture, const QPointF& spawn)
		: QGraphicsPixmapItem(Game::GAME->playableArea),
			cleanup(false),
			timeAlive(0) {
	setPixmap(QPixmap(texture.texture));
	setZValue(texture.zValue);
	setOffset(-boundingRect().center());
	setPos(spawn);

	Game::GAME->addEntity(this);
}

void BaseEntity::moveFoward(const double& distance) {
	double rot = qDegreesToRadians(rotation());
	double dx = distance * -sin(rot);
	double dy = distance * cos(rot);

	moveBy(dx, dy);
}

void BaseEntity::moveTowardsPoint(const QPointF& point,
																	const double& distance) {
	QVector2D dir(point - pos());
	dir.normalize();
	dir *= distance;
	moveBy(dir.x(), dir.y());
}

void BaseEntity::rotate(const double& deg) { setRotation(rotation() + deg); }

Bullet* BaseEntity::fireBullet(const Bullets& info,
															 const QPointF& spawn,
															 const double& rotation) {
	return new Bullet(info, this, pos() + spawn, rotation);
}

QList<Bullet*> BaseEntity::fireBulletCircle(const Bullets& info,
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

QList<Bullet*> BaseEntity::fireBulletArc(const Bullets& info,
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

double BaseEntity::distanceSquared(BaseEntity* entity) {
	return pow(pos().x() - entity->pos().x(), 2) +
				 pow(pos().y() - entity->pos().y(), 2);
}

QPointF BaseEntity::confineToPlayableArea(const QPointF& pos) {
	return QPointF(qBound(Game::GAME->playableArea->boundingRect().left() -
														boundingRect().left(),
												pos.x(),
												Game::GAME->playableArea->boundingRect().right() -
														boundingRect().right()),
								 qBound(Game::GAME->playableArea->boundingRect().top() -
														boundingRect().top(),
												pos.y(),
												Game::GAME->playableArea->boundingRect().bottom() -
														boundingRect().bottom()));
}

bool BaseEntity::isOnScreen() {
	return collidesWithItem(Game::GAME->playableArea);
}

bool BaseEntity::cycle(const int& dur) { return cycle(dur, 0, 0); }

bool BaseEntity::cycle(const int& dur, const int& time) {
	return cycle(dur, time, time);
}

bool BaseEntity::cycle(const int& dur, const int& low, const int& high) {
	return (timeAlive % dur >= low && timeAlive % dur <= high);
}
