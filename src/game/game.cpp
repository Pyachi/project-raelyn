#include "game.h"
#include "src/entity/entities/player.h"
#include "src/entity/entities/bullet.h"
#include "src/entity/entities/enemy.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

Game::Game() : QGraphicsView() {
    scene = new QGraphicsScene(0, 0, gameWidth, gameHeight);
    setScene(scene);

    background = new QGraphicsPixmapItem();
    QPixmap backgroundImage(gameHeight - (playBorder * 2),gameHeight - (playBorder * 2));
		backgroundImage.fill(Qt::darkBlue);
    background->setPixmap(backgroundImage);
    background->setOffset(playBorder, playBorder);
    scene->addItem(background);

    setFixedSize(gameWidth + 2, gameHeight + 2);

    QTimer* tickClock = new QTimer();
    tickClock->start(1000/60);
    connect(tickClock, &QTimer::timeout, this, &Game::tick);

    new Player(this);
		new Enemy(this, ":/images/enemy.png", QPoint(40,100), 2, 200);
}

void Game::tick() {
    foreach(Entity* entity, entities) {
        entity->tick();
        if (entity->cleanup) {
            entities.remove(entity);
            scene->removeItem(entity);
        }
    }
}

QSet<int> Game::getKeys() const {
    return keys;
}

void Game::addEntity(Entity *entity) {
    entities.insert(entity);
}

void Game::keyPressEvent(QKeyEvent *e) {
    keys.insert(e->key());
    QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent *e) {
    keys.remove(e->key());
    QGraphicsView::keyReleaseEvent(e);
}
