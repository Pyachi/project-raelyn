#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QTimer>
#include <QOpenGLWidget>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "util.h"
#include "uid.h"
#include "entityplayer.h"
#include "user.h"
#include <QGraphicsWidget>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QPushButton>

class Game : public QGraphicsView {
	Q_OBJECT
	//***************************************************************************
	// Basics
	Game(void);
	~Game(void);

	static Game* GAME;

	//***************************************************************************
	// Window
	QTimer timer;
	QOpenGLWidget openGL;
	QGraphicsScene scene;
	QGraphicsRectItem play;
	QGraphicsPixmapItem sidebar;
	QGraphicsSimpleTextItem gameOver;
	//***************************************************************************
	// Background
	QGraphicsPixmapItem background1;
	QGraphicsPixmapItem background2;
	QGraphicsPixmapItem background3;
	QGraphicsPixmapItem background4;
	//***************************************************************************
	// Sidebar
	QGraphicsSimpleTextItem highScore;
	QGraphicsSimpleTextItem score;
	Array<QGraphicsPixmapItem*> healthDisplay;
	Array<QGraphicsPixmapItem*> bombsDisplay;
	QGraphicsSimpleTextItem powerDisplay;
	//***************************************************************************
	// Scoreboard Display
	QGraphicsRectItem scoreboardDisplay;
	Array<QGraphicsSimpleTextItem*> scoreboards;
	QGraphicsProxyWidget menuButtonProxy;
	QPushButton* menuButton;
	bool menuReturn;
	//***************************************************************************
	// Gameplay
	bool paused = false;
	ushort health = 3;
	ushort bombs = 3;
	ushort power = 0;
	ulong age = 0;
	Map<UID, Entity*> entities;
	List<std::function<void(Game&)> > eventQueue;
	Map<ushort, List<std::function<void(Game&)> > > timedEventQueue;
	void tick(void);
	//***************************************************************************
	// Controls
	QSet<int> keys;
	void keyPressEvent(QKeyEvent* e) {
		keys.insert(e->key());
		QGraphicsView::keyPressEvent(e);
	}
	void keyReleaseEvent(QKeyEvent* e) {
		keys.remove(e->key());
		QGraphicsView::keyReleaseEvent(e);
	}
	//***************************************************************************
	// Public Interface
 public:
  static void create(void);
	static bool playerAlive(void);
	static EntityPlayer* getPlayer(void);
	static void addEntity(Entity* entity);
	static void queueEvent(std::function<void(Game&)> func, ushort time = 0);
	static void updateScoreboard(void);
	static void pause(void);
	static void returnToMenu(void);

	static void takeDamage(void);
	static void gainHealth(void);
	static void gainBomb(void);
	static void gainPower(void);
	//***************************************************************************
	// Getters
	static QGraphicsRectItem& getPlayableArea(void) { return GAME->play; }
	static QSet<int>& getKeys(void) { return GAME->keys; }
	static Map<UID, Entity*>& getEntities(void) { return GAME->entities; }
	//***************************************************************************
};

#endif  // SCENE_H
