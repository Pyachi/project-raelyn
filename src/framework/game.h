#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QSet>
#include <QTimer>
#include "alias.h"
#include "src/ai/playerai.h"
#include "src/network/uuid.h"

class Entity;
class Player;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
	Q_OBJECT

 public:
	static void create();
	static QSet<int> getKeys();
	static Player* getPlayer();
	static QMap<UUID, Entity*> getEntities();
	static QGraphicsPixmapItem& getPlayableArea();
	static void addEntity(Entity*);
	static void queueEvent(std::function<void(void)>);

 private:
	Game();

	static Game* GAME;

	QTimer timer;
	QOpenGLWidget openGL;
	QGraphicsScene scene;
	QGraphicsPixmapItem playableArea;
	QGraphicsPixmapItem background;

	QMap<UUID, Entity*> entities;
	List<std::function<void(void)> > eventQueue;

	QSet<int> keys;

	void tick();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

	friend class Connection;
};

#endif  // SCENE_H
