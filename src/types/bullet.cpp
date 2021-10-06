#include "bullet.h"
#include "src/assets/textures.h"

Bullet::Bullet(Game* game,
							 Texture texture,
							 QPoint spawn,
							 BaseEntity* owner,
							 std::function<void(Bullet*)> ai,
							 double rotation)
		: BaseEntity(game, texture, spawn),
			LinkedEntity(game, texture, spawn, owner),
			AIEntity<Bullet>(game, texture, spawn, ai),
			CollidableEntity(game, texture, spawn) {
	setRotation(rotation);
}

void Bullet::tick() {
	BaseEntity::tick();
	AIEntity::tick(this);
}
