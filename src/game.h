#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QSet>

class BaseEntity;
class PlayerInfo;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
	Q_OBJECT

 public:
	Game(const PlayerInfo&, const QString&);

	QGraphicsPixmapItem* playableArea;

	QSet<int> getKeys();
	QSet<BaseEntity*> getEntities();
	void addEntity(BaseEntity*);

 private:
	QGraphicsScene* scene;
	QGraphicsPixmapItem* background;
	QSet<BaseEntity*> entities;
	QSet<int> keys;

	void tick();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
};

#endif  // SCENE_H
