#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QSet>

class BaseEntity;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
	Q_OBJECT

 public:
	Game();
	QGraphicsScene* scene;

	QSet<int> getKeys() const;
	void addEntity(BaseEntity*);

 private:
	QGraphicsPixmapItem* background;
	QSet<BaseEntity*> entities;
	QSet<int> keys;

	void tick();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif  // SCENE_H
