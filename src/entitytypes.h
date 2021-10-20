#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>
#include "texture.h"

template <class T>
using EntityAI = std::function<void(T*)>;

class Game;
class Player;
class Enemy;
class Bullet;
class PlayerHitbox;
class BulletInfo;

class BaseEntity : public QGraphicsPixmapItem {
 public:
	BaseEntity(Game*, const Texture&, const QPointF&);

	bool cleanup;
	int timeAlive;

	void moveFoward(const double&);
	void rotate(const double&);

	Bullet* fireBullet(const BulletInfo&, const QPointF&, const double& = 0);
	QList<Bullet*> fireBulletCircle(const BulletInfo&,
																	const QPointF&,
																	const int&,
																	const double& = 0);
	Enemy* getNearestEnemy();
	QList<BaseEntity*> getCollisions();

	QPointF confineToPlayableArea(const QPointF&);
	bool isOnScreen();

	bool cycle(const int&);
	bool cycle(const int&, const int&);
	bool cycle(const int&, const int&, const int&);

	virtual void tick() = 0;

 protected:
	Game* game;
};

class LinkedEntity {
 public:
	LinkedEntity(BaseEntity*);

	BaseEntity* owner;
};

class CollidableEntity {
 public:
	CollidableEntity();
	virtual ~CollidableEntity();
};

template <class T>
class AIEntity : public BaseEntity {
 public:
	AIEntity(Game*, const Texture&, const EntityAI<T>&, const QPointF&);

	const EntityAI<T> ai;
};

template <class T>
AIEntity<T>::AIEntity(Game* game,
											const Texture& texture,
											const EntityAI<T>& ai,
											const QPointF& spawn)
		: BaseEntity(game, texture, spawn), ai(ai) {}

#endif  // ENTITYTYPES_H
