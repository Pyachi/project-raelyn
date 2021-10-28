#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

using BulletAI = EntityAI<Bullet>;

class Bullets {
 public:
	static const Bullets PLAYERBASIC;
	static const Bullets PLAYERHOMING;
	static const Bullets ACCELERATING;
	static const Bullets SCREENWRAPTEST;
	static const Bullets FLOWER;

	const Texture& texture;
	const BulletAI ai;

 private:
	Bullets(const Texture&, const BulletAI&);
};

class Bullet : public BaseEntity {
 public:
	Bullet(const Bullets&, BaseEntity*, const QPointF&, double);

	bool borderCheck;
	BaseEntity* owner;

 private:
	const BulletAI ai;
	void tick() override;
};

#endif  // BULLET_H
