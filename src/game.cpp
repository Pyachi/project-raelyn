#include "game.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include "ai.h"
#include "entities.h"
#include "entityinfo.h"
#include "entitytypes.h"
#include "textures.h"

Game::Game() : QGraphicsView() {
	scene = new QGraphicsScene(0, 0, gameWidth, gameHeight);
	setScene(scene);

	setInteractive(false);
	setViewport(new QOpenGLWidget);

	background = new QGraphicsPixmapItem();
	QPixmap backgroundImage(gameHeight - (playBorder * 2),
													gameHeight - (playBorder * 2));
	backgroundImage.fill(Qt::darkRed);
	background->setPixmap(backgroundImage);
	background->setOffset(playBorder, playBorder);
	scene->addItem(background);

	setFixedSize(gameWidth + 2, gameHeight + 2);

	QTimer* tickClock = new QTimer();
	tickClock->start(1000 / 60);
	connect(tickClock, &QTimer::timeout, this, &Game::tick);

	new Player(this, Players::player1, QPointF(400, 400));
//	new Enemy(this, Enemies::enemy2, QPointF(260, 100));
	new Enemy(this, Enemies::enemy1, QPointF(360, 100));
}

void Game::tick() {
	foreach (BaseEntity* entity, entities) {
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

void Game::addEntity(BaseEntity* entity) {
	entities.insert(entity);
	scene->addItem(entity);
}

void Game::keyPressEvent(QKeyEvent* e) {
	keys.insert(e->key());
	QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent* e) {
	keys.remove(e->key());
	QGraphicsView::keyReleaseEvent(e);
}

QSet<BaseEntity*> Game::getEntities() {
	return entities;
}
