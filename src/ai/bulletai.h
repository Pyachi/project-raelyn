#ifndef BULLETS_H
#define BULLETS_H

#include "alias.h"
#include "src/assets/texture.h"
#include <QPointF>

class Bullet;
class Entity;

struct BulletInfo {
	BulletInfo(const Texture&,
						 const AI<Bullet>&,
						 double = 0,
						 const QPointF& = QPointF(0, 0),
						 int = 1);
	const Texture& texture;
	const AI<Bullet>& ai;
	double relRot;
	QPointF relLoc;
	int damage;

	Bullet* spawn(const Entity*,
								double = 0,
								const QPointF& = QPointF(0, 0)) const;
};

namespace BulletType {
extern const AI<Bullet> PLAYERBASIC;
extern const AI<Bullet> PLAYERHOMING;
extern const AI<Bullet> BASIC8;
extern const AI<Bullet> BASIC10;
extern const AI<Bullet> BASIC12;
extern const AI<Bullet> ACCELERATING;
extern const AI<Bullet> SCREENWRAPTEST;
extern const AI<Bullet> FLOWER;
};

#endif  // BULLETS_H
