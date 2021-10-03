#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>

class Game;

class Entity : public QGraphicsPixmapItem {
public:
    Entity(Game*, QString texture, QPoint spawnLoc, int zValue);

    int getLeftX();
    int getRightX();
    int getTopY();
    int getBottomY();

    QPoint getCenter();
    void setCenter(QPoint);
    bool borderCollision(QPointF &pos);

    virtual void tick() {}

    bool cleanup = false;

protected:
    Game* game;
};

#endif // ENTITY_H
