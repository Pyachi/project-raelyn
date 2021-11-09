#ifndef BULLETS_H
#define BULLETS_H

#include <QPointF>
#include "alias.h"
#include "src/assets/texture.h"
#include "src/entity/entity.h"

enum BulletAI {
	AI_PLAYERBASIC,
	AI_PLAYERHOMING,
	AI_BASIC8,
	AI_BASIC10,
	AI_BASIC12,
	AI_ACCELERATING,
	AI_SCREENWRAPTEST,
	AI_FLOWER
};

class EntityBullet;

namespace Bullets {
extern AI<EntityBullet> get(BulletAI);
}

struct BulletInfo {
	BulletInfo(Tex, BulletAI, double = 0, const QPointF& = {0, 0}, int = 1);
	const Tex texture;
	const BulletAI ai;
	const double relRot;
	const QPointF relLoc;
	const int damage;

	EntityBullet* spawn(const Entity* owner,
											double = 0,
											const QPointF& = {0, 0}) const;
};

#endif  // BULLETS_H
