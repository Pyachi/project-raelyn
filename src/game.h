#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QOpenGLWidget>
#include "alias.h"
#include <QSet>
#include "src/ai/playerai.h"

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
	static List<Entity*> getEntities();
	static Player* getPlayer();
	static QGraphicsPixmapItem& getPlayableArea();
	static void addEntity(Entity*);
	static void updatePlayerLocation(const QString&, const QPointF&);
	static void removeOnlinePlayer(const QString&);
	static void addOnlinePlayer(PlayerType, const QString&);

 private:
	Game();

	static Game* GAME;

	QTimer timer;
	QOpenGLWidget openGL;
	QGraphicsScene scene;
	QGraphicsPixmapItem playableArea;
	QGraphicsPixmapItem background;

	Player* player;
	List<Entity*> entities;
	Map<QString, Player*> onlinePlayers;
	List<std::function<void(void)> > onlineQueue;

	QSet<int> keys;

	void tick();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif  // SCENE_H