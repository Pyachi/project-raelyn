#ifndef SCENE_H
#define SCENE_H

#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QSet>
#include <QTimer>
#include "entity.h"
#include "uid.h"
#include "user.h"
#include "util.h"

class Entity;
class EntityPlayer;
class Game;

class Game : public QGraphicsView {
  Q_OBJECT

 public:
  static void create(void);
  static EntityPlayer* getPlayer(void);
  static bool isPlayerAlive(void) {
    return GAME->entities.count(User::getUID());
  }

  static QSet<int> getKeys(void) { return GAME->keys; }
  static Map<UID, Entity*>& getEntities(void) { return GAME->entities; }
	static QGraphicsRectItem& getPlayableArea(void) { return GAME->playableArea; }

  static void addEntity(Entity* entity) {
		queueEvent(
				{[entity](Game& game) { game.entities.insert({entity->id, entity}); }});
  }
	static void queueEvent(std::function<void(Game&)> func, int time = 0) {
		if (GAME == nullptr) {
			qDebug() << "ERROR: Attempted to queue event before Game exists!";
      return;
		}
		if (time == 0)
			GAME->eventQueue.push_back(func);
		else if (GAME->timedEventQueue.count(time))
			GAME->timedEventQueue[time].emplace_back(func);
    else
			GAME->timedEventQueue.insert({time, {func}});
  }

	static Game* get() { return GAME; }
	static void pause() {
		if (GAME == nullptr) {
			qDebug() << "ERROR: Attempted to pause before Game exists!";
			return;
		}
		GAME->paused = true;
	}

 private:
  Game(void);
  ~Game(void);

  static Game* GAME;

  QTimer timer;
  QOpenGLWidget openGL;
  QGraphicsScene scene;
  QGraphicsRectItem playableArea;
  QGraphicsPixmapItem background1;
  QGraphicsPixmapItem background2;
  QGraphicsPixmapItem background3;
  QGraphicsPixmapItem background4;
  QGraphicsPixmapItem screen;
  QGraphicsSimpleTextItem dead;
  QDialog popup;
  QLabel popupText;
  QGridLayout popupLayout;
  QPushButton menuButton;
  QGraphicsSimpleTextItem points;
  QGraphicsSimpleTextItem power;

  bool paused;
  Map<UID, Entity*> entities;
	List<std::function<void(Game&)> > eventQueue;
	Map<int, List<std::function<void(Game&)> > > timedEventQueue;

  QSet<int> keys;

  void tick(void);

  void keyPressEvent(QKeyEvent* e) {
    keys.insert(e->key());
    QGraphicsView::keyPressEvent(e);
  }
  void keyReleaseEvent(QKeyEvent* e) {
    keys.remove(e->key());
    QGraphicsView::keyReleaseEvent(e);
  }
  void mouseMoveEvent(QMouseEvent* e) {
    qDebug() << e->pos();
    QGraphicsView::mouseMoveEvent(e);
  }

	friend struct Runnable;
};

#endif  // SCENE_H
