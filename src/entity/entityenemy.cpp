#include "entityenemy.h"
#include "Framework"
#include "Entity"
#include "Assets"
#include "AI"
#include "Network"

EntityEnemy::EntityEnemy(Texture tex, UID id, int health, AI<EntityEnemy> ai)
		: Entity(ENEMY, tex, id), health(health), ai(ai) {}

void EntityEnemy::tick(void) {
	age++;
	ai(this);
	handleMovement();
	List<EntityBullet*> bullets;
	for (Entity* entity : getCollisions(BULLET)) {
		EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
		if (bullet->ownerType == PLAYER || bullet->ownerType == ONLINEPLAYER)
			bullets.push_back(bullet);
	}
	for (EntityBullet* bullet : bullets) {
        SFX::playSound(SFX_EXPL_LIGHT1, 10);
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
	for (int i = 0; i < (Random::getInt() % 5) + 5; i++)
		Collectables::spawn(COLLECTABLE_POWER, pos());
	for (int i = 0; i < (Random::getInt() % 20) + 10; i++)
		Collectables::spawn(COLLECTABLE_POINTS, pos());
	deleteLater();
}
