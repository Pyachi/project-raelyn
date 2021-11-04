#include "game.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include "src/entity/enemy.h"
#include "src/entity/onlineplayer.h"
#include "src/entity/player.h"
#include "src/texture.h"

Game* Game::GAME = nullptr;

Game::Game() : QGraphicsView(), scene(0, 0, gameWidth, gameHeight) {
	GAME = this;
	setScene(&scene);

	setInteractive(false);
	setViewport(new QOpenGLWidget);

	QPixmap backgroundPixmap(Texture::BACKGROUND.texture);
	background.setPixmap(backgroundPixmap);
	background.setZValue(Texture::BACKGROUND.zValue);
	scene.addItem(&background);

	QPixmap playableAreaPixmap(gameHeight - (playBorder * 2),
														 gameHeight - (playBorder * 2));
	playableAreaPixmap.fill(Qt::darkRed);
	playableArea.setPixmap(playableAreaPixmap);
	playableArea.setOffset(-playableArea.boundingRect().center());
	playableArea.setPos(playBorder + playableArea.boundingRect().width() / 2,
											playBorder + playableArea.boundingRect().height() / 2);
	scene.addItem(&playableArea);

	setFixedSize(gameWidth + 2, gameHeight + 2);

	QTimer* tickClock = new QTimer();
	tickClock->start(1000 / 60);
	connect(tickClock, &QTimer::timeout, this, &Game::tick);

	new Player(Players::PYACHI, QPointF(0, 200));
	new Enemy(Texture::ENEMY1,
						MovementPatterns::LEFTRIGHTTEST,
						FiringPatterns::ENEMY1,
						50,
						QPointF(0, -300));
}

void Game::tick() {
	foreach(Entity * entity, entities) {
		entity->tick();
		if (entity->cleanup) {
			entities.remove(entity);
			scene.removeItem(entity);
		}
	}
}

void Game::create() {
	if (GAME == nullptr)
		GAME = new Game();
	GAME->show();
}

QSet<int> Game::getKeys() { return GAME->keys; }

QSet<Entity*> Game::getEntities() { return GAME->entities; }

void Game::addEntity(Entity* entity) { GAME->entities.insert(entity); }

void Game::keyPressEvent(QKeyEvent* e) {
	keys.insert(e->key());
	QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent* e) {
	keys.remove(e->key());
	QGraphicsView::keyReleaseEvent(e);
}

QGraphicsPixmapItem* Game::getPlayableArea() { return &GAME->playableArea; }

void Game::updatePlayerLocation(const QString& user, const QPointF& loc) {
	if (GAME->onlinePlayers.value(user) == nullptr) {
		GAME->onlinePlayers.insert(user, new OnlinePlayer(Texture::PLAYER1, loc));
	} else
		GAME->onlinePlayers.value(user)->setPos(loc);
}
