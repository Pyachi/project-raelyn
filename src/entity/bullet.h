#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullets {
 public:
	static const Bullets PLAYERBASIC;
	static const Bullets PLAYERHOMING;
	static const Bullets ACCELERATING;
	static const Bullets SCREENWRAPTEST;
	static const Bullets FLOWER;

	const Texture& texture;
	const EntityAI<Bullet> ai;

 private:
	Bullets(const Texture&, const EntityAI<Bullet>&);
};

class Bullet : public Entity {
 public:
	Bullet(const Bullets&, Entity*, const QPointF&, double);

	bool borderCheck;
	Entity* owner;

 private:
	const EntityAI<Bullet> ai;
	void tick() override;
};

#endif  // BULLET_H
