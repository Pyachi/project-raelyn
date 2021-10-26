#ifndef AI_H
#define AI_H

#include "entitytypes.h"

using FiringPattern = EntityAI<Player>;
using EnemyAI = EntityAI<Enemy>;
using BulletAI = EntityAI<Bullet>;

class PlayerInfo {
 public:
	static const PlayerInfo PYACHI;
	static const PlayerInfo AERON;

	const Texture& texture;
	const FiringPattern firingPattern;
	const int normalSpeed;
	const int focusSpeed;

 private:
	PlayerInfo(const Texture&, const FiringPattern&, int, int);
};

class EnemyInfo {
 public:
	static const EnemyInfo ENEMY1;

	const Texture& texture;
	const EnemyAI ai;
	const int health;

 private:
	EnemyInfo(const Texture&, const EnemyAI&, int);
};

class BulletInfo {
 public:
	static const BulletInfo PLAYERBASIC;
	static const BulletInfo PLAYERHOMING;
	static const BulletInfo ACCELERATING;
	static const BulletInfo SCREENWRAPTEST;
	static const BulletInfo FLOWER;

	const Texture& texture;
	const BulletAI ai;

 private:
	BulletInfo(const Texture&, const BulletAI&);
};

#endif  // AI_H
