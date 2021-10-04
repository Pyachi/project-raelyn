#include "linkedentity.h"

LinkedEntity::LinkedEntity(Game* game,
													 Texture texture,
													 QPoint spawn,
													 BaseEntity* owner)
		: BaseEntity(game, texture, spawn) {
	this->owner = owner;
}

BaseEntity* LinkedEntity::getOwner() {
	return owner;
}
