#include "entitytypes.h"
#include <QVector2D>
#include <QtMath>
#include "bullet.h"
#include "enemy.h"
#include "game.h"

BaseEntity::BaseEntity(Game* game, const Texture& texture, const QPointF& spawn)
		: QGraphicsPixmapItem(game->background),
			cleanup(false),
			timeAlive(0),
			game(game) {
	setPixmap(QPixmap(texture.texture));
	setZValue(texture.zValue);
	setOffset(-boundingRect().center());
	setPos(spawn);

	game->addEntity(this);
}

LinkedEntity::LinkedEntity(BaseEntity* owner) : owner(owner) {}

CollidableEntity::CollidableEntity() {}

void BaseEntity::moveFoward(const double& distance) {
	double rot = qDegreesToRadians(rotation());
	double dx = distance * -sin(rot);
	double dy = distance * cos(rot);

	moveBy(dx, dy);
}

void BaseEntity::rotate(const double& deg) {
	setRotation(rotation() + deg);
}

Bullet* BaseEntity::fireBullet(const BulletInfo& info,
															 const QPointF& spawn,
															 const double& rotation) {
	return new Bullet(game, info, this, pos() + spawn, rotation);
}

QList<Bullet*> BaseEntity::fireBulletCircle(const BulletInfo& info,
																						const QPointF& spawn,
																						const int& count,
																						const double& startRotation) {
	QList<Bullet*> list;
	double rotation = startRotation;
	for (int i = 0; i < count; i++) {
		list.append(new Bullet(game, info, this, pos() + spawn, rotation));
		rotation += 360 / count;
	}
	return list;
}

Enemy* BaseEntity::getNearestEnemy() {
	Enemy* closest = nullptr;
	float closestDis = 99999999;
	foreach (BaseEntity* entity, game->getEntities()) {
		if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
			float distance = QVector2D(enemy->pos()).lengthSquared();
			if (distance < closestDis) {
				closest = enemy;
				closestDis = distance;
			}
		}
	}
	return closest;
}

QList<BaseEntity*> BaseEntity::getCollisions() {
	QList<BaseEntity*> list;
	foreach (QGraphicsItem* item, collidingItems()) {
		if (dynamic_cast<CollidableEntity*>(item))
			list.append(dynamic_cast<BaseEntity*>(item));
	}
	return list;
}

QPointF BaseEntity::confineToPlayableArea(const QPointF& pos) {
	return QPointF(
			qBound(game->background->boundingRect().left() - boundingRect().left(),
						 pos.x(),
						 game->background->boundingRect().right() - boundingRect().right()),
			qBound(
					game->background->boundingRect().top() - boundingRect().top(),
					pos.y(),
					game->background->boundingRect().bottom() - boundingRect().bottom()));
}

bool BaseEntity::isOnScreen() {
	return collidesWithItem(game->background);
}

bool BaseEntity::cycle(const int& dur) {
	return cycle(dur, 0, 0);
}

bool BaseEntity::cycle(const int& dur, const int& time) {
	return cycle(dur, time, time);
}

bool BaseEntity::cycle(const int& dur, const int& low, const int& high) {
	return (timeAlive % dur >= low && timeAlive % dur <= high);
}

CollidableEntity::~CollidableEntity() {}
