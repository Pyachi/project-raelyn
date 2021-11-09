#ifndef BULLETS_H
#define BULLETS_H

#include <QPointF>
#include "alias.h"
#include "src/assets/texture.h"
#include "src/entity/entity.h"

class EntityBullet;

enum BulletAI {
	PLAYERBASIC,
	PLAYERHOMING,
	BASIC8,
	BASIC10,
	BASIC12,
	ACCELERATING,
	SCREENWRAPTEST,
	FLOWER,
};

struct BulletInfo {
	BulletInfo(Tex,
						 BulletAI,
						 double = 0,
						 const QPointF& = QPointF(0, 0),
						 int = 1);
	const Tex texture;
	const BulletAI ai;
	const double relRot;
	const QPointF relLoc;
	const int damage;

	EntityBullet* spawn(const Entity* owner,
											double = 0,
											const QPointF& = QPointF(0, 0)) const;
};

namespace Bullets {
extern AI<EntityBullet> get(BulletAI);
}

#endif  // BULLETS_H
