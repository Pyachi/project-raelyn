#ifndef BULLETS_H
#define BULLETS_H

#include <QPointF>
#include <functional>

class Texture;
class Bullet;
class Entity;

using BulletAI = std::function<void(Bullet*)>;

struct BulletInfo {
	BulletInfo(const Texture&,
						 const BulletAI&,
						 double = 0,
						 QPointF = QPointF(0, 0));

	const Texture& texture;
	const BulletAI& ai;
	double relRot;
	QPointF relPos;

	Bullet* spawn(Entity*, const QPointF&, double) const;
};

namespace BulletType {
extern const BulletAI PLAYERBASIC;
extern const BulletAI PLAYERHOMING;
extern const BulletAI BASIC8;
extern const BulletAI BASIC10;
extern const BulletAI BASIC12;
extern const BulletAI ACCELERATING;
extern const BulletAI SCREENWRAPTEST;
extern const BulletAI FLOWER;
};

#endif  // BULLETS_H
