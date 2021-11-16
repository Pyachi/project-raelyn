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

class Game : public QGraphicsView {
  Q_OBJECT

 public:
  static void create(void);
  static EntityPlayer* getPlayer(void);

  static QSet<int> getKeys(void) { return GAME->keys; }
  static Map<UID, Entity*>& getEntities(void) { return GAME->entities; }
  static QGraphicsRectItem& getPlayableArea(void) { return GAME->playableArea; }
  static void addEntity(Entity* entity) {
    queueEvent([entity]() { GAME->entities.insert({entity->id, entity}); });
  }
  static void queueEvent(std::function<void(void)> func) {
    if (GAME == nullptr)
      return;
    GAME->eventQueue.push_back(func);
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
  QGraphicsPixmapItem screen;
  QGraphicsSimpleTextItem dead;
  QDialog popup;
  QLabel popupText;
  QGridLayout popupLayout;
  QPushButton menuButton;
  QGraphicsSimpleTextItem points;

  bool paused;
  int age;
  Map<UID, Entity*> entities;
  List<std::function<void(void)> > eventQueue;

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

  friend class Connection;
};

#endif  // SCENE_H
