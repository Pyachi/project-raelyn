#include "playerhitbox.h"

PlayerHitbox::PlayerHitbox(Game* game, BaseEntity* owner)
		: AIEntity<PlayerHitbox>(
					game,
					Texture::PLAYERHITBOX,
					[](PlayerHitbox* hitbox) { hitbox->setPos(hitbox->owner->pos()); },
					owner->pos()),
			LinkedEntity(owner),
			CollidableEntity() {}

void PlayerHitbox::tick() {
	timeAlive++;
	ai(this);
}
