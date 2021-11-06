#include "game.h"
#include <QOpenGLWidget>
#include "src/assets/texture.h"
#include <QTimer>
#include "src/entity/player.h"
#include "src/ai/enemytype.h"
#include "src/network/connection.h"
#include <QKeyEvent>

Game* Game::GAME = nullptr;

Game::Game() : QGraphicsView(), scene(0, 0, gameWidth, gameHeight) {
	GAME = this;
	setScene(&scene);

	setInteractive(false);
	setViewport(new QOpenGLWidget);

	QPixmap backgroundPixmap(Textures::BACKGROUND.texture);
	background.setPixmap(backgroundPixmap);
	background.setZValue(Textures::BACKGROUND.zValue);
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
}

void Game::tick() {
	foreach(Entity * entity, entities) {
		entity->tick();
		if (entity->readyToDelete()) {
			entities.remove(entity);
			scene.removeItem(entity);
		}
	}
}

void Game::create() {
	if (GAME == nullptr)
		GAME = new Game();
	GAME->show();
	Connection::sendPacket(Packet(PACKETPLAYINPLAYERSPAWN));
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
	Player* player = GAME->players.value(user);
	if (player != nullptr)
		player->setPos(loc);
}

void Game::removePlayer(const QString& user) {
	Player* player = GAME->players.take(user);
	if (player != nullptr)
		player->deleteLater();
}

void Game::addPlayer(PlayerType type, const QString& user) {
	Player* player = new Player(type, QPointF(0, 0), user);
	GAME->players.insert(user, player);
}
