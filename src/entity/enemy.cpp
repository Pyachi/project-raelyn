#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "src/game.h"
#include "src/assets/sfx.h"
#include "src/ai/enemyai.h"
#include "src/ai/collectableai.h"
#include "src/network/connection.h"
#include "src/network/packet.h"

Enemy::Enemy(const EnemyInfo& info, UUID id)
		: Entity(ENEMY, info.texture, id), health(info.health), ai(info.ai) {
	Game::addEntity(this);
}

void Enemy::tick() {
	age++;
	ai(this);
	List<Bullet*> bullets;
	for (Entity* entity : getCollisions(BULLET)) {
		Bullet* bullet = dynamic_cast<Bullet*>(entity);
		if (bullet->ownerType == PLAYER || bullet->ownerType == ONLINEPLAYER)
			bullets.push_back(bullet);
	}
	for (Bullet* bullet : bullets) {
		SFX::playSound(SFX::EXPL_LIGHT_2, 0.1);
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

void Enemy::kill() {
	if (cleanup)
		return;
	for (int i = 0; i < 10; i++)
		Collectables::POWER.spawn(pos());
	deleteLater();
}
