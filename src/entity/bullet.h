#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullet;

using BulletAI = std::function<void(Bullet*)>;

class Bullet : public Entity {
 public:
	Entity* getOwner() const;
	bool borderCheck;

 private:
	Bullet(const BulletInfo*, Entity*, const QPointF&, double);

	Entity* owner;

	const BulletAI& ai;

	void tick() override;

	friend class BulletInfo;
};

#endif  // BULLET_H
