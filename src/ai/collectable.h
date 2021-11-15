#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "util.h"

class EntityCollectable;
class EntityPlayer;
class Texture;

class Collectable {
  Collectable(const Texture& tex, const AI<EntityPlayer>& ai)
      : tex(tex), ai(ai) {}

  Collectable(const Collectable& col) = delete;

  const Texture& tex;
  const AI<EntityPlayer> ai;

 public:
	EntityCollectable* spawn(const QPointF& loc, int maxDis = 0) const;

  static const Collectable POWER;
  static const Collectable POINTS;
  static const Collectable HEALTH;
  static const Collectable BOMB;
};

#endif  // COLLECTABLE_H
