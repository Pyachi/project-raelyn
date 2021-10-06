#include "entities.h"
#include "textures.h"
#include "entityinfo.h"

Player::Player(Game* game, PlayerInfo* info, QPointF spawn)
		: BaseEntity(game, info->texture, spawn) {

}

void Player::tick() {
	//bunch o' stuff :)
}

Enemy::Enemy(Game* game, EnemyInfo* info, QPointF spawn)
		: BaseEntity(game, info->texture, spawn),
			CollidableEntity(),
			AIEntity<Enemy>(info->ai) {
	health = info->health;
}

void Enemy::tick() { AIEntity::tick(this); }

Bullet::Bullet(Game* game,
							 BulletInfo* info,
							 BaseEntity* owner,
							 QPointF spawn,
							 qreal rotation)
		: BaseEntity(game, info->texture, spawn),
			LinkedEntity(owner),
			CollidableEntity(),
			AIEntity<Bullet>(info->ai) {
	setRotation(rotation);
}

void Bullet::tick() { AIEntity::tick(this); }

PlayerHitbox::PlayerHitbox(Game* game, BaseEntity* owner)
		: BaseEntity(game, &Textures::playerHitbox, owner->pos()),
			LinkedEntity(owner),
			CollidableEntity() {}

void PlayerHitbox::tick() { setPos(owner->pos()); }
