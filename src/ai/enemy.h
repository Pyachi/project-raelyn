#ifndef ENEMY_H
#define ENEMY_H

#include "util.h"

class EntityEnemy;
class Texture;
class UID;

class Enemy {
	static Array<Ref<Enemy> > list;

  Enemy(const Texture& tex, int health, const AI<EntityEnemy>& ai)
      : index(list.size()), tex(tex), health(health), ai(ai) {
    list.push_back(*this);
  }

  Enemy(const Enemy& enemy) = delete;

  const int index;

  const Texture& tex;
  const int health;
  const AI<EntityEnemy> ai;

 public:
  EntityEnemy* spawn(const QPointF& loc, const UID& id) const;

	operator int() const { return index; }

  static const Enemy& valueOf(int i) { return list[i]; }
	static const Array<Ref<Enemy> >& values() { return list; }

  static const Enemy ENEMYTEST1;
  static const Enemy ENEMYTEST2;
  static const Enemy SIMPLESHOTGUN_TOP_LEFT;
  static const Enemy SIMPLESHOTGUN_TOP_RIGHT;
  static const Enemy TANKYBANG_UP_DOWN;
  static const Enemy SIMPLESHOTGUN_MID_LEFT_UP;
  static const Enemy SIMPLESHOTGUN_MID_RIGHT_UP;
  static const Enemy WAVE1BASIC;
  static const Enemy DIVER;
  static const Enemy LARGE_SLOW_LEFTTORIGHT;
  static const Enemy LARGE_SLOW_RIGHTTOLEFT;
  static const Enemy small_fast_RIGHTTOLEFT;
  static const Enemy small_fast_LEFTTORIGHT;
  static const Enemy small_fast_TOPDOWNTOLEFT;
  static const Enemy small_fast_TOPDOWNTORIGHT;
};

#endif  // ENEMY_H
