#ifndef BULLETS_H
#define BULLETS_H

#include <QPointF>
#include "src/assets/texture.h"
#include "util.h"

class Entity;

enum BulletAI {
  AI_PLAYERBASIC,
  AI_PLAYERHOMING,
  AI_BASIC8,
  AI_BASIC10,
  AI_BASIC12,
  AI_ACCELERATING,
  AI_SCREENWRAPTEST,
  AI_FLOWER,
};

class EntityBullet;

namespace Bullets {
extern AI<EntityBullet> get(BulletAI);
}

struct BulletInfo {
	BulletInfo(BulletAI, double = 0, const QPointF& = {0, 0});
  const BulletAI ai;
  const double relRot;
  const QPointF relLoc;

	EntityBullet* spawn(Texture,
											const Entity*,
                      double = 0,
											const QPointF& = {0, 0},
											int = 1) const;
};

#endif  // BULLETS_H
