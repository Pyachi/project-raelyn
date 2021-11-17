#include "entityenemy.h"
#include "collectable.h"
#include "connection.h"
#include "entitybullet.h"
#include "packet.h"
#include "sfx.h"
#include "user.h"

EntityEnemy::EntityEnemy(const Texture& tex,
                         const UID& id,
                         int health,
                         const AI<EntityEnemy>& ai)
    : Entity(ENEMY, tex, id), health(health), ai(ai) {}

void EntityEnemy::tick(void) {
  age++;
  ai(this);
  handleMovement();
  List<EntityBullet*> bullets;
  for (Entity* entity : getNearbyEntities(BULLET, 40)) {
    EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
    if (bullet->ownerType == PLAYER || bullet->ownerType == ONLINEPLAYER)
      bullets.push_back(bullet);
  }
  for (EntityBullet* bullet : bullets) {
    SFX::EXPL_LIGHT1.play(10);
    health -= bullet->damage;
		User::addScore(bullet->damage);
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
  for (Entity* entity : getNearbyEntities(BULLET, 60)) {
    EntityBullet* bullet = dynamic_cast<EntityBullet*>(entity);
    if (bullet->ownerType == ENEMY || bullet->ownerType == BULLET) {
			Collectable::POINTS.spawn(bullet->pos(), 0, 0);
      bullet->deleteLater();
    }
  }
  for (int i = 0; i < (Random::getInt() % 5) + 3; i++)
		Collectable::POWER.spawn(pos());
  for (int i = 0; i < (Random::getInt() % 5) + 3; i++)
		Collectable::POINTS.spawn(pos());
  deleteLater();
}
