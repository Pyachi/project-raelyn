#include "playerhitbox.h"
#include "bullet.h"
#include "enemy.h"
#include "src/assets/textures.h"

template <typename T, typename K>
inline bool isType(const K& k) {
	return typeid(T).hash_code() == typeid(k).hash_code();
}

PlayerHitbox::PlayerHitbox(Game* game, Texture texture, BaseEntity* owner)
		: BaseEntity(game, texture, owner->getCenter()),
			LinkedEntity(game, texture, owner->getCenter(), owner),
			CollidableEntity(game, texture, owner->getCenter()) {}

void PlayerHitbox::tick() {
	BaseEntity::tick();
	setCenter(owner->getCenter());
}
