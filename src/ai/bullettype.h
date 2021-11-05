#ifndef BULLETS_H
#define BULLETS_H

#include <functional>

class Bullet;

using BulletAI = std::function<void(Bullet*)>;

class BulletType {
 public:
	static const BulletAI PLAYERBASIC;
	static const BulletAI PLAYERHOMING;
	static const BulletAI BASIC8;
	static const BulletAI BASIC10;
	static const BulletAI BASIC12;
	static const BulletAI ACCELERATING;
	static const BulletAI SCREENWRAPTEST;
	static const BulletAI FLOWER;
};

#endif  // BULLETS_H
