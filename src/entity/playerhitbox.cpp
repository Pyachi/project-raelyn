#include "playerhitbox.h"
#include "src/texture.h"

PlayerHitbox::PlayerHitbox(Entity* owner)
		: Entity(Texture::PLAYERHITBOX, owner->pos()),
			owner(owner),
			ai([](PlayerHitbox* hitbox) { hitbox->setPos(hitbox->owner->pos()); }) {}

void PlayerHitbox::tick() {
	timeAlive++;
	ai(this);
}
