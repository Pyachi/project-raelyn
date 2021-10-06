#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H

#include <QGraphicsPixmapItem>

struct Texture;
struct PlayerInfo;
struct EnemyInfo;
struct BulletInfo;
class Game;
class Bullet;
class CollidableEntity;

template <class T>
using EntityAI = std::function<void(T*)>;

class BaseEntity : virtual public QGraphicsPixmapItem {
 public:
	BaseEntity(Game*, Texture&, QPointF);

	bool cleanup;
	int timeAlive;
	Game* game;

	void moveFoward(int);
	void setCenter(QPointF);
	QPointF getCenter();
	Bullet* fireBullet(BulletInfo&, QPointF, qreal);
	QList<CollidableEntity*> getCollidingEntities();

	virtual void tick() = 0;
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
	AIEntity(Game*, Texture&, QPointF, EntityAI<T>&);

	EntityAI<T>& ai;
};

template <class T>
AIEntity<T>::AIEntity(Game* game,
											Texture& texture,
											QPointF spawn,
											EntityAI<T>& ai)
		: BaseEntity(game, texture, spawn), ai(ai) {}

class PlayerHitbox : public AIEntity<PlayerHitbox>,
										 public LinkedEntity,
										 public CollidableEntity {
 public:
	PlayerHitbox(Game*, BaseEntity*);

	void tick() override;
};

class Player : public AIEntity<Player> {
 public:
	Player(Game*, PlayerInfo&, QPointF);

	PlayerHitbox* hitbox;

	bool firing;
	bool focus;
	int level;

	bool isHit();

	void tick() override;
};

class Enemy : public AIEntity<Enemy>, public CollidableEntity {
 public:
	Enemy(Game*, EnemyInfo&, QPointF);

	int health;

	QList<Bullet*> getHits();

	void tick() override;
};

class Bullet : public AIEntity<Bullet>,
							 public LinkedEntity,
							 public CollidableEntity {
 public:
	Bullet(Game*, BulletInfo&, BaseEntity*, QPointF, qreal);

	bool boundsCheck;

	void tick() override;
};

#endif  // ENTITYTYPES_H
