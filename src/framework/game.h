#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QOpenGLWidget>
#include <QSet>
#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "alias.h"
#include "src/ai/player.h"
#include "src/network/uuid.h"

class Entity;
class EntityPlayer;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
	Q_OBJECT

 public:
	static void create();
	static QSet<int> getKeys();
	static EntityPlayer* getPlayer();
	static QMap<UUID, Entity*> getEntities();
	static QGraphicsPixmapItem& getPlayableArea();
	static void addEntity(Entity*);
	static void queueEvent(std::function<void(void)>);

 private:
	Game();
	~Game();

	static Game* GAME;

	QTimer timer;
	QOpenGLWidget openGL;
	QGraphicsScene scene;
	QGraphicsPixmapItem playableArea;
	QGraphicsPixmapItem background;
	QDialog popup;
	QLabel popupText;
	QGridLayout popupLayout;
	QPushButton menuButton;

	bool paused;
	QMap<UUID, Entity*> entities;
	List<std::function<void(void)> > eventQueue;

	QSet<int> keys;

	void tick();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

	friend class Connection;
};

#endif  // SCENE_H
