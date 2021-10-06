#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <QPointF>

class Texture;
class Player;
class Enemy;
class Bullet;
class Game;
class BaseEntity;

template <class T>
using EntityAI = std::function<void(T*)>;

class PlayerInfo {
 public:
	PlayerInfo(Texture*);

	Player* create(Game*, QPointF);

	Texture* texture;
};

class EnemyInfo {
 public:
	EnemyInfo(Texture*, EntityAI<Enemy>*, int);

	Enemy* create(Game*, QPointF);

	Texture* texture;
	EntityAI<Enemy>* ai;
	int health;
};

class BulletInfo {
 public:
	BulletInfo(Texture*, EntityAI<Bullet>*);

	Bullet* create(Game*, BaseEntity*, QPointF, qreal);

	Texture* texture;
	EntityAI<Bullet>* ai;
};

#endif  // ENTITYINFO_H
