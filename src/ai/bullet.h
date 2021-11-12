#ifndef BULLETS_H
#define BULLETS_H

#include "util.h"
#include "texture.h"

enum BulletAI {
	AI_PLAYERBASIC,
	AI_PLAYERHOMING,
	AI_BASIC1,
	AI_BASIC2,
	AI_BASIC3,
	AI_BASIC4,
	AI_BASIC5,
	AI_BASIC6,
	AI_BASIC7,
	AI_BASIC8,
	AI_BASIC9,
	AI_BASIC10,
	AI_BASIC11,
	AI_BASIC12,
	AI_ACCELERATING,
	AI_SCREENWRAPTEST,
	AI_FLOWER,
};

class Entity;
class EntityBullet;
struct BulletInfo;

namespace Bullets {
extern AI<EntityBullet> get(BulletAI);
extern EntityBullet* spawn(BulletAI ai,
													 BulletInfo info,
													 Texture tex,
													 const Entity* owner,
													 double rot = 0,
													 const QPointF& loc = {0, 0},
													 int scale = 1,
													 int damage = 1);
}

#endif  // BULLETS_H
