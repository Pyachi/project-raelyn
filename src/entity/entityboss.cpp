#include "entityboss.h"
#include "Framework"
#include "Entity"
#include "Assets"
#include "Network"
#include "AI"

EntityBoss::EntityBoss(Texture tex,
											 UID id,
											 int health,
											 int phaseCount,
											 AI<EntityBoss> ai)
		: Entity(ENEMY, tex, id),
			health(health),
			phase(phaseCount),
			phaseHealth(health),
			ai(ai) {}

void EntityBoss::tick(void) {
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
		SFX::playSound(SFX_EXPL_LIGHT2, 10);
		health -= bullet->damage;
		bullet->deleteLater();
		if (health <= 0) {
			advancePhase();
			Connection::sendPacket(
					{PACKETPLAYINADVANCEPHASE, QStringList() << id.toString()});
			break;
		}
	}
}

void EntityBoss::kill(void) {
	if (cleanup)
		return;
	for (int i = 0; i < (Random::getInt() % 5) + 50; i++)
		Collectables::spawn(COLLECTABLE_POWER, pos());
	for (int i = 0; i < (Random::getInt() % 20) + 100; i++)
		Collectables::spawn(COLLECTABLE_POINTS, pos());
	Connection::sendPacket(PACKETPLAYINRESUMELEVEL);
	deleteLater();
}

void EntityBoss::advancePhase() {
	phase--;
	if (phase == 0) {
		kill();
		return;
	} else {
		health = phaseHealth;
		age = 0;
		for (int i = 0; i < (Random::getInt() % 5) + 5; i++)
			Collectables::spawn(COLLECTABLE_POWER, pos());
		for (int i = 0; i < (Random::getInt() % 20) + 10; i++)
			Collectables::spawn(COLLECTABLE_POINTS, pos());
	}
}
