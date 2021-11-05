#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullet;

using BulletAI = std::function<void(Bullet*)>;

class Bullet : public Entity {
 public:
	Entity* owner;
	bool borderCheck;

 private:
	Bullet(const BulletInfo*, Entity*, const QPointF&, double);

	const BulletAI& ai;

	void tick() override;

	friend class BulletInfo;
};

#endif  // BULLET_H
