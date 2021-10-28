#include "game.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include "src/texture.h"
#include "src/entity/player.h"
#include "src/entity/enemy.h"

Game* Game::GAME = nullptr;

Game::Game()
		: QGraphicsView(),
			playableArea(new QGraphicsPixmapItem),
			scene(new QGraphicsScene(0, 0, gameWidth, gameHeight)),
			background(new QGraphicsPixmapItem) {
	GAME = this;
	setScene(scene);

	setInteractive(false);
	setViewport(new QOpenGLWidget);

	QPixmap backgroundPixmap(Texture::BACKGROUND.texture);
	background->setPixmap(backgroundPixmap);
	background->setZValue(Texture::BACKGROUND.zValue);
	scene->addItem(background);

	QPixmap playableAreaPixmap(gameHeight - (playBorder * 2),
														 gameHeight - (playBorder * 2));
	playableAreaPixmap.fill(Qt::darkRed);
	playableArea->setPixmap(playableAreaPixmap);
	playableArea->setOffset(-playableArea->boundingRect().center());
	playableArea->setPos(playBorder + playableArea->boundingRect().width() / 2,
											 playBorder + playableArea->boundingRect().height() / 2);
	scene->addItem(playableArea);

	setFixedSize(gameWidth + 2, gameHeight + 2);

	QTimer* tickClock = new QTimer();
	tickClock->start(1000 / 60);
	connect(tickClock, &QTimer::timeout, this, &Game::tick);

	new Player(Players::PYACHI, QPointF(0, 200));
	new Enemy(Enemies::ENEMY1, QPointF(0, -300));
}

void Game::tick() {
	foreach(BaseEntity * entity, entities) {
		entity->tick();
		if (entity->cleanup) {
			entities.remove(entity);
			scene->removeItem(entity);
		}
	}
}

QSet<int> Game::getKeys() { return keys; }

QSet<BaseEntity*> Game::getEntities() { return entities; }

void Game::addEntity(BaseEntity* entity) { entities.insert(entity); }

void Game::keyPressEvent(QKeyEvent* e) {
	keys.insert(e->key());
	QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent* e) {
	keys.remove(e->key());
	QGraphicsView::keyReleaseEvent(e);
}
