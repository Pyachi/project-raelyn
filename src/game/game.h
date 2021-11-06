#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QSet>
#include "src/ai/playertype.h"

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
	static QSet<Entity*> getEntities();
	static void addEntity(Entity*);
	static QGraphicsPixmapItem* getPlayableArea();
	static void addPlayer(PlayerType, const QString&);
	static void removePlayer(const QString&);
	static void updatePlayerLocation(const QString&, const QPointF&);

 private:
	Game();

	static Game* GAME;

	QGraphicsScene scene;
	QGraphicsPixmapItem playableArea;
	QGraphicsPixmapItem background;
	QSet<Entity*> entities;

	QMap<QString, Player*> players;

	QSet<int> keys;

	void tick();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif  // SCENE_H
