#ifndef BULLETINFO_H
#define BULLETINFO_H

#include <QPointF>

class Texture;
class Bullet;
class Entity;

using BulletAI = std::function<void(Bullet*)>;

class BulletInfo {
 public:
	BulletInfo(const Texture&,
						 const BulletAI&,
						 double = 0,
						 const QPointF& = QPointF(0, 0));

	const Texture& texture;
	const BulletAI& ai;
	double relRot;
	QPointF relPos;

	Bullet* spawn(Entity*, const QPointF&, double) const;
};

#endif  // BULLETINFO_H
