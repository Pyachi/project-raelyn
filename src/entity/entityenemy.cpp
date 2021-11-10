#include "entityenemy.h"
#include "entitybullet.h"
#include "entityplayer.h"
#include "src/ai/collectable.h"
#include "src/ai/enemy.h"
#include "src/assets/sfx.h"
#include "src/framework/game.h"
#include "src/network/connection.h"
#include "src/network/packet.h"

EntityEnemy::EntityEnemy(Tex tex, UUID id, int health, AI<EntityEnemy> ai)
		: Entity(ENEMY, tex, id), health(health), ai(ai) {
	Game::addEntity(this);
}

void EntityEnemy::tick(void) {
	age++;
	ai(this);
	List<EntityBullet*> bullets;
	for (Entity* entity : getCollisions(BULLET)) {
		EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
		if (bullet->ownerType == PLAYER || bullet->ownerType == ONLINEPLAYER)
			bullets.push_back(bullet);
	}
	for (EntityBullet* bullet : bullets) {
		SFX::playSound(EXPL_LIGHT_2, 0.1);
		health -= bullet->damage;
		bullet->deleteLater();
		if (health <= 0) {
			kill();
			Connection::sendPacket(
					{PACKETPLAYINENEMYDEATH, QStringList() << id.toString()});
			break;
		}
	}
}

void EntityEnemy::kill(void) {
	if (cleanup)
		return;
	for (int i = 0; i < (Random::getInt() % 5) + 8; i++)
		Collectables::spawn(POWER, pos());
	deleteLater();
}
