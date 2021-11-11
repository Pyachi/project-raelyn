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
#include "util.h"
#include "src/ai/player.h"
#include "src/network/uid.h"

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
	static QMap<UID, Entity*> getEntities(void);
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
	QMap<UID, Entity*> entities;
	List<std::function<void(void)> > eventQueue;

	QSet<int> keys;

	void tick(void);

	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);

	friend class Connection;
};

#endif  // SCENE_H
