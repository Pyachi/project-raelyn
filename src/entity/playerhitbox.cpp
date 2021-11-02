#include "playerhitbox.h"

PlayerHitbox::PlayerHitbox(BaseEntity* owner)
		: BaseEntity(Texture::PLAYERHITBOX, owner->pos()),
			owner(owner),
			ai([](PlayerHitbox* hitbox) { hitbox->setPos(hitbox->owner->pos()); }) {}

void PlayerHitbox::tick() {
	timeAlive++;
	ai(this);
}
