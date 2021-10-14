#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <QPointF>
#include <functional>

struct Texture;
class Player;
class Enemy;
class Bullet;

template <class T>
using EntityAI = std::function<void(T*)>;

struct PlayerInfo {
	PlayerInfo(Texture&, EntityAI<Player>&);

	Texture& texture;
	EntityAI<Player>& ai;
};

struct EnemyInfo {
	EnemyInfo(Texture&, EntityAI<Enemy>&, int);

	Texture& texture;
	EntityAI<Enemy>& ai;
	int health;
};

struct BulletInfo {
	BulletInfo(Texture&, EntityAI<Bullet>&, bool = true);

	Texture& texture;
	EntityAI<Bullet>& ai;
	bool boundsCheck;
};

#endif  // ENTITYINFO_H
