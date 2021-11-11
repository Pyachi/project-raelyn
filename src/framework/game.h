#ifndef SCENE_H
#define SCENE_H

#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QSet>
#include <QTimer>
#include "src/ai/player.h"
#include "src/network/uid.h"
#include "util.h"

class Entity;
class EntityPlayer;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
	Q_OBJECT

 public:
	static void create(void);
	static QSet<int> getKeys(void);
	static EntityPlayer* getPlayer(void);
	static Map<UID, Entity*> getEntities(void);
	static QGraphicsPixmapItem& getPlayableArea(void);
	static void addEntity(Entity*);
	static void queueEvent(std::function<void(void)>);

 private:
	Game(void);
	~Game(void);

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
	Map<UID, Entity*> entities;
	List<std::function<void(void)> > eventQueue;

	QSet<int> keys;

	void tick(void);

	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);

	friend class Connection;
};

#endif  // SCENE_H
