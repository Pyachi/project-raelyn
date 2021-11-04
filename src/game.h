#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QSet>

class Entity;
class Players;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
	Q_OBJECT

 public:
	Game();

	static Game* GAME;

	void screenShake();

	QGraphicsPixmapItem* playableArea;
	QSet<int> getKeys();
	QSet<Entity*> getEntities();
	void addEntity(Entity*);

 private:
	QGraphicsScene* scene;
	QGraphicsPixmapItem* background;
	QSet<Entity*> entities;
	QSet<int> keys;

	void tick();

	bool shake;
	int shakeTimer;

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif  // SCENE_H
