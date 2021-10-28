#include "playerhitbox.h"

PlayerHitbox::PlayerHitbox(BaseEntity* owner)
		: BaseEntity(Texture::PLAYERHITBOX, owner->pos()),
			ai([](PlayerHitbox* hitbox) { hitbox->setPos(hitbox->owner->pos()); }),
			owner(owner) {}

void PlayerHitbox::tick() {
	timeAlive++;
	ai(this);
}
