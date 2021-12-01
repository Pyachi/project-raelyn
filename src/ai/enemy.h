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
	EntityEnemy* spawn(const QPointF& loc, const UID& id, double scale) const;

	operator int() const { return index; }

	static const Enemy& valueOf(int i) { return list[i]; }
  static const Array<Ref<Enemy> >& values() { return list; }

  static const Enemy ENEMYTEST1;  // ID 0
  static const Enemy ENEMYTEST2;
  static const Enemy SIMPLESHOTGUN_TOP_LEFT;
  static const Enemy SIMPLESHOTGUN_TOP_RIGHT;
  static const Enemy TANKYBANG_UP_DOWN;
  static const Enemy SIMPLESHOTGUN_MID_LEFT_UP;
  static const Enemy SIMPLESHOTGUN_MID_RIGHT_UP;
  static const Enemy WAVE1BASIC;
  static const Enemy DIVER;
  static const Enemy LARGE_SLOW_LEFTTORIGHT;
  static const Enemy LARGE_SLOW_RIGHTTOLEFT;  // ID 10
  static const Enemy SMALL_FAST_RIGHTTOLEFT;
  static const Enemy SMALL_FAST_LEFTTORIGHT;
  static const Enemy SMALL_FAST_TOPDOWNTOLEFT;
  static const Enemy SMALL_FAST_TOPDOWNTORIGHT;
  static const Enemy DART1;
  static const Enemy DART2;
  static const Enemy DART3;
  static const Enemy DART4;
  static const Enemy DART5;
  static const Enemy DART6;  // ID 20
  static const Enemy SUNEASY;
  static const Enemy WHEEL;
  static const Enemy SUN;
  static const Enemy WHEELEASY;
};

#endif  // ENEMY_H
