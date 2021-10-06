#include "entitytypes.h"
#include "textures.h"
#include "game.h"

BaseEntity::BaseEntity(Game* game, Texture* texture, QPointF spawn) {
	this->game = game;

	setPixmap(QPixmap(texture->getTexture()));
	setZValue(texture->getZValue());
	setTransformOriginPoint(QPointF(pixmap().width() / 2, pixmap().height() / 2));
	setPos(spawn);

	game->addEntity(this);
}

LinkedEntity::LinkedEntity(BaseEntity* owner) { this->owner = owner; }

CollidableEntity::CollidableEntity() {}

bool BaseEntity::isInsideBorder() { return true; }

void BaseEntity::moveFoward(int distance) {
	qreal dx = -cos(rotation()) * distance;
	qreal dy = sin(rotation()) * distance;
	moveBy(dx, dy);
}

