#include "entityboss.h"
#include "collectable.h"
#include "connection.h"
#include "entitybullet.h"
#include "packet.h"
#include "sfx.h"

EntityBoss::EntityBoss(const Texture& tex,
                       const UID& id,
                       const Array<int>& health,
                       const AI<EntityBoss>& ai)
    : Entity(ENEMY, tex, id),
      health(health[0]),
      phase(0),
      totalHealth(health),
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
    SFX::EXPL_LIGHT2.play(10);
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
		Collectable::POWER.spawn(pos(), 200);
	for (int i = 0; i < (Random::getInt() % 20) + 100; i++)
		Collectable::POINTS.spawn(pos(), 200);
  Connection::sendPacket(PACKETPLAYINRESUMELEVEL);
  deleteLater();
}

void EntityBoss::advancePhase() {
  phase++;
  for (Entity* entity : getNearbyEntities(BULLET, 1000000)) {
    EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
    if (bullet->ownerType == BULLET || bullet->ownerType == ENEMY) {
			Collectable::POINTS.spawn(bullet->pos(), 0, 0);
      bullet->deleteLater();
    }
  }
  if (phase == totalHealth.size()) {
    kill();
    return;
  } else {
    health = totalHealth[phase];
    age = 0;
    for (int i = 0; i < (Random::getInt() % 5) + 5; i++)
			Collectable::POWER.spawn(pos(), 100);
    for (int i = 0; i < (Random::getInt() % 20) + 10; i++)
			Collectable::POINTS.spawn(pos(), 100);
  }
}
