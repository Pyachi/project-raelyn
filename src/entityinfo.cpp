#include "entityinfo.h"
#include "entities.h"

PlayerInfo::PlayerInfo(Texture* texture) { this->texture = texture; }

EnemyInfo::EnemyInfo(Texture* texture, EntityAI<Enemy>* ai, int health) {
	this->texture = texture;
	this->ai = ai;
	this->health = health;
}

BulletInfo::BulletInfo(Texture* texture, EntityAI<Bullet>* ai) {
	this->texture = texture;
	this->ai = ai;
}

Player* PlayerInfo::create(Game* game, QPointF spawn) {
	return new Player(game, this, spawn);
}

Enemy* EnemyInfo::create(Game* game, QPointF spawn) {
	return new Enemy(game, this, spawn);
}

Bullet* BulletInfo::create(Game* game,
													 BaseEntity* owner,
													 QPointF spawn,
													 qreal rotation) {
	return new Bullet(game, this, owner, spawn, rotation);
}
