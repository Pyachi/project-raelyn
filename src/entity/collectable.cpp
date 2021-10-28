#include "collectable.h"

CollectableType::CollectableType(const Texture& texture,
																 const CollectableAI& ai)
		: texture(texture), ai(ai) {}

Collectable::Collectable(const CollectableType& type, const QPointF& spawn)
		: BaseEntity(type.texture, spawn), ai(type.ai) {}

const CollectableType CollectableType::POWER =
		CollectableType(Texture::PLAYERHITBOX, [](Collectable* entity) {
			int dir = rand() % 360;
			if (entity->timeAlive < 10)
				entity->moveBy(20 * -sin(dir), 20 * cos(dir));
			else
				entity->moveBy(0, entity->timeAlive / 30.0);
		});

void Collectable::tick() {
	timeAlive++;
	ai(this);
}
