#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QGraphicsPixmapItem>
#include "src/assets/textures.h"

class Game;
class Bullet;

class BaseEntity : virtual public QGraphicsPixmapItem {
 public:
	BaseEntity(Game*, Texture, QPoint);

	bool cleanup = false;
	int time = 0;

	bool borderCollision(QPointF&);
	Bullet* fireBullet(Texture, QPoint, std::function<void(Bullet*)>, double);

	int getLeftX();
	int getRightX();
	int getTopY();
	int getBottomY();
	int getSize();
	QPoint getCenter();
	void setCenter(QPoint);
	void moveFoward(int);

 protected:
	Game* game;

	virtual void tick();

	friend class Game;
};

#endif  // BASEENTITY_H
