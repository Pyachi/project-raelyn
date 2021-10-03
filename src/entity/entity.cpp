#include "entity.h"
#include "src/game/game.h"
#include <stdlib.h>

Entity::Entity(Game* game, QString texture, QPoint spawnLoc, int zValue) : QGraphicsPixmapItem() {
    this->game = game;
		QPixmap image(texture);
		setPixmap(image);
    setCenter(spawnLoc);
    setZValue(zValue);

    game->scene->addItem(this);

    game->addEntity(this);
}

bool Entity::borderCollision(QPointF &pos) {
    double min = playBorder;
    double max = gameHeight - (playBorder + pixmap().width());
    double x = pos.x();
    double y = pos.y();
    pos.setX(qBound(min, pos.x(), max));
    pos.setY(qBound(min, pos.y(), max));
    return (x != pos.x() || y != pos.y());
}

int Entity::getLeftX() {
    return int(x());
}

int Entity::getRightX() {
    return getLeftX() + pixmap().width();
}

int Entity::getTopY() {
    return int(y());
}

int Entity::getBottomY() {
    return getTopY() + pixmap().height();
}

QPoint Entity::getCenter() {
    return QPoint((getLeftX() + getRightX())/2, (getTopY() + getBottomY())/2);
}

void Entity::setCenter(QPoint pos) {
    setPos(pos - QPoint(pixmap().width()/2, pixmap().height()/2));
}
