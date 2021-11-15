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
#include "uid.h"
#include "util.h"

class Entity;
class EntityPlayer;

class Game : public QGraphicsView {
  Q_OBJECT

 public:
  static void create(void);
  static QSet<int> getKeys(void);
  static EntityPlayer* getPlayer(void);
  static Map<UID, Entity*> getEntities(void);
  static QGraphicsRectItem& getPlayableArea(void);
  static void addEntity(Entity* entity);
  static void queueEvent(std::function<void(void)>);

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

  bool paused;
  int age;
  Map<UID, Entity*> entities;
  List<std::function<void(void)> > eventQueue;

  QSet<int> keys;

  void tick(void);

  void keyPressEvent(QKeyEvent* e);
  void keyReleaseEvent(QKeyEvent* e);

  friend class Connection;
};

#endif  // SCENE_H
