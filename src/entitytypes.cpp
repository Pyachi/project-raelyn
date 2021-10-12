#include "entitytypes.h"
#include <QtMath>
#include "ai.h"
#include "entityinfo.h"
#include "game.h"
#include "textures.h"
#include "utilities.h"
#include <QVector2D>

BaseEntity::BaseEntity(Game* game, Texture& texture, QPointF spawn)
		: cleanup(false), timeAlive(0), game(game) {
	setPixmap(QPixmap(texture.texture));
	setZValue(texture.zValue);
	setTransformOriginPoint(boundingRect().center());
	setCenter(spawn);

	game->addEntity(this);
}

LinkedEntity::LinkedEntity(BaseEntity* owner) : owner(owner) {}

CollidableEntity::CollidableEntity() {}

CollidableEntity::~CollidableEntity() {}

void BaseEntity::moveFoward(int distance) {
	double rot = qDegreesToRadians(rotation());
	double dx = distance * -sin(rot);
	double dy = distance * cos(rot);

	moveBy(dx, dy);
}

void BaseEntity::setCenter(QPointF pos) {
	setPos(pos - boundingRect().center());
}

QPointF BaseEntity::getCenter() {
	return pos() + boundingRect().center();
}

Bullet* BaseEntity::fireBullet(BulletInfo& info,
															 QPointF spawn,
															 qreal rotation) {
	return new Bullet(game, info, this, getCenter() + spawn, rotation);
}

QList<CollidableEntity*> BaseEntity::getCollidingEntities() {
	QList<CollidableEntity*> list;
	foreach (QGraphicsItem* item, collidingItems()) {
		if (CollidableEntity* entity = dynamic_cast<CollidableEntity*>(item))
			list.append(entity);
	}
	return list;
}

PlayerHitbox::PlayerHitbox(Game* game, BaseEntity* owner)
		: AIEntity<PlayerHitbox>(game,
														 Textures::playerHitbox,
														 owner->pos(),
														 AI::playerHitbox),
			LinkedEntity(owner),
			CollidableEntity() {}

Player::Player(Game* game, PlayerInfo& info, QPointF spawn)
		: AIEntity<Player>(game, info.texture, spawn, info.ai),
			hitbox(new PlayerHitbox(game, this)),
			firing(false),
			focus(false),
			level(1) {}

Enemy::Enemy(Game* game, EnemyInfo& info, QPointF spawn)
		: AIEntity<Enemy>(game, info.texture, spawn, info.ai),
			CollidableEntity(),
			health(info.health) {}

Bullet::Bullet(Game* game,
							 BulletInfo& info,
							 BaseEntity* owner,
							 QPointF spawn,
							 qreal rotation)
		: AIEntity<Bullet>(game, info.texture, spawn, info.ai),
			LinkedEntity(owner),
			CollidableEntity(),
			boundsCheck(info.boundsCheck) {
	setRotation(rotation);
}

bool Player::isHit() {
	foreach (CollidableEntity* entity, hitbox->getCollidingEntities()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Enemy*>(bullet->owner))
				return true;
		if (Enemy* enemy = dynamic_cast<Enemy*>(entity))
			return true;
	}
	return false;
}

QList<Bullet*> Enemy::getHits() {
	QList<Bullet*> list;
	foreach (CollidableEntity* entity, getCollidingEntities()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(entity))
			if (dynamic_cast<Player*>(bullet->owner))
				list.append(bullet);
	}
	return list;
}

void PlayerHitbox::tick() {
	timeAlive++;
	ai(this);
}

void Player::tick() {
	ai(this);
	timeAlive++;
}

void Enemy::tick() {
	setPos(pos() + (move / 10));
	move -= move / 10;
	foreach (BaseEntity* entity, getHits()) {
		health--;
		if (health == 0)
			cleanup = true;
		entity->cleanup = true;
	}
	ai(this);
	timeAlive++;
}

bool BaseEntity::cycle(int dur) {
	return cycle(dur, 0, 0);
}

bool BaseEntity::cycle(int dur, int time) {
	return cycle(dur, time, time);
}

bool BaseEntity::cycle(int dur, int low, int high) {
	return (timeAlive % dur >= low && timeAlive % dur <= high);
}

void Bullet::tick() {
	QPointF checkPos = pos();
	if (boundsCheck && Util::confineToPlayableArea(checkPos, pixmap().size()))
		cleanup = true;
	ai(this);
	timeAlive++;
}

Enemy* BaseEntity::getNearestEnemy() {
	Enemy* closest = nullptr;
	float closestDis = 99999999;
	foreach (BaseEntity* entity, game->getEntities()) {
		if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
			float distance = QVector2D(enemy->pos()).lengthSquared();
			if (distance < closestDis) {
				closest = enemy;
				closestDis = distance;
			}
		}
	}
	return closest;
}
