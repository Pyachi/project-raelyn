#include "baseentity.h"
#include <QtMath>
#include "src/textures.h"
#include "src/entity/entities/bullet.h"
#include "src/game/game.h"

BaseEntity::BaseEntity(Game* game, Texture texture, QPoint spawn)
		: QGraphicsPixmapItem() {
	this->game = game;

	setPixmap(QPixmap(texture.getTexture()));
	setZValue(texture.getZValue());
	setTransformOriginPoint(QPointF(getSize() / 2, getSize() / 2));

	setCenter(spawn);

	game->addEntity(this);
}

void BaseEntity::tick() {
	time++;
}

Bullet* BaseEntity::fireBullet(Texture texture,
															 QPoint spawn,
															 std::function<void(Bullet*)> ai,
															 double rotation) {
	return new Bullet(game, texture, spawn, this, ai, rotation);
}

void BaseEntity::moveFoward(int dis) {
	double rot = qDegreesToRadians(rotation());
	double dx = dis * -sin(rot);
	double dy = dis * cos(rot);
	moveBy(dx, dy);
}

bool BaseEntity::borderCollision(QPointF& pos) {
	double min = playBorder;
	double max = gameHeight - (playBorder + pixmap().width());
	double x = pos.x();
	double y = pos.y();
	pos.setX(qBound(min, pos.x(), max));
	pos.setY(qBound(min, pos.y(), max));
	return (x != pos.x() || y != pos.y());
}

int BaseEntity::getLeftX() {
	return int(x());
}

int BaseEntity::getRightX() {
	return getLeftX() + pixmap().width();
}

int BaseEntity::getTopY() {
	return int(y());
}

int BaseEntity::getBottomY() {
	return getTopY() + pixmap().height();
}

int BaseEntity::getSize() {
	return pixmap().height();
}

QPoint BaseEntity::getCenter() {
	return QPoint((getLeftX() + getRightX()) / 2, (getTopY() + getBottomY()) / 2);
}

void BaseEntity::setCenter(QPoint pos) {
	setPos(pos - QPoint(pixmap().width() / 2, pixmap().height() / 2));
}
