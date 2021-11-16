#ifndef BULLET_H
#define BULLET_H

#include "util.h"

class EntityBullet;
class Texture;

class Bullet {
  Bullet(const AI<EntityBullet>& ai) : ai(ai) {}

  Bullet(const Bullet& bullet) = delete;

  const AI<EntityBullet> ai;

 public:
	operator const AI<EntityBullet> &() const { return ai; }

  static const Bullet BASIC1;
  static const Bullet BASIC2;
  static const Bullet BASIC3;
  static const Bullet BASIC4;
  static const Bullet BASIC5;
  static const Bullet BASIC6;
  static const Bullet BASIC7;
  static const Bullet BASIC8;
  static const Bullet BASIC9;
  static const Bullet BASIC10;
  static const Bullet BASIC11;
  static const Bullet BASIC12;
  static const Bullet BASIC40;
};

struct SpawnInfo {
  SpawnInfo(double rot = 0, const QPointF& loc = {0, 0}) : rot(rot), loc(loc) {}
  const double rot;
  const QPointF loc;

  operator const List<SpawnInfo>() const { return {*this}; }
};

const List<SpawnInfo> operator<<(const List<SpawnInfo>& list1,
                                 const SpawnInfo& info);
const List<SpawnInfo> operator<<(const List<SpawnInfo>& list1,
                                 const List<SpawnInfo>& list2);

class Pattern {
  Pattern(const List<SpawnInfo>& pattern) : pattern(pattern) {}

  Pattern(const Pattern& pattern) = delete;

  const List<SpawnInfo> pattern;

 public:
	operator const List<SpawnInfo> &() const { return pattern; }

	static const Pattern CIRCLE3;
  static const Pattern CIRCLE4;
	static const Pattern CIRCLE6;
  static const Pattern CIRCLE8;
	static const Pattern CIRCLE12;
  static const Pattern CIRCLE16;
  static const Pattern SHOTGUN3;
  static const Pattern SHOTGUN5;
};

struct BulletInfo {
  BulletInfo(const AI<EntityBullet>& ai,
             const Texture& tex,
             const List<SpawnInfo>& info = SpawnInfo(),
             int scale = 1,
             int damage = 1)
      : ai(ai), tex(tex), info(info), scale(scale), damage(damage) {}
  const AI<EntityBullet> ai;
  const Texture& tex;
  const List<SpawnInfo> info;
  const int scale;
  const int damage;

  operator const List<BulletInfo>() const { return {*this}; }
};

const List<BulletInfo> operator<<(const List<BulletInfo>& list1,
                                  const BulletInfo& info);
const List<BulletInfo> operator<<(const List<BulletInfo>& list1,
                                  const List<BulletInfo>& list2);

#endif  // BULLET_H
