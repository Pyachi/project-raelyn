#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QTimer>

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

	new Player(this);
	new Enemy(this, Textures::enemy1, QPoint(360, 100), AI::enemy, 500);
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
