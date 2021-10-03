#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QSet>

class Entity;

const int gameWidth = 1280;
const int gameHeight = 720;
const int playBorder = 20;

class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game();
    QGraphicsScene* scene;

    QSet<int> getKeys() const;
    void addEntity(Entity*);


private:
    QGraphicsPixmapItem* background;
    QSet<Entity*> entities;
    QSet<int> keys;

    void tick();

    virtual void keyPressEvent(QKeyEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);
};

#endif // SCENE_H
