#ifndef BOSS_H
#define BOSS_H

#include "util.h"

class EntityBoss;
class Texture;
class UID;

class Boss {
	static Array<Ref<Boss> > list;

  Boss(const Texture& tex, const Array<int>& health, const AI<EntityBoss>& ai)
      : index(list.size()), tex(tex), health(health), ai(ai) {
    list.push_back(*this);
  }

  Boss(const Boss& boss) = delete;

  const int index;
  const Texture& tex;
  const Array<int> health;
  const AI<EntityBoss> ai;

 public:
	EntityBoss* spawn(const QPointF& loc, const UID& id, int scale) const;

	operator int() const { return index; }

  static const Boss& valueOf(int i) { return list[i]; }

  static const Boss LVL1MINI;
  static const Boss LVL1;
  static const Boss LVL2MINI;
  static const Boss LVL2;
  static const Boss LVL3MINI;
  static const Boss LVL3;
};

#endif  // BOSS_H
