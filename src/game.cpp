#include "game.h"
#include <QOpenGLWidget>
#include "src/assets/texture.h"
#include <QTimer>
#include "src/entity/player.h"
#include "src/ai/enemytype.h"
#include "src/network/connection.h"
#include <QKeyEvent>
#include "src/network/user.h"
#include "menu.h"

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

	player = new Player(PYACHI, QPointF(0, 250), User::getName());

	Enemies::ENEMYTEST.spawn(QPointF(0, -300));
}

void Game::tick() {
	foreach(Entity * entity, entities) {
		entity->tick();
		if (entity->readyToDelete()) {
			entities.remove(entity);
			scene.removeItem(entity);
		}
	}
	if (player != nullptr) {
		player->tick();
		if (player->readyToDelete()) {
			close();
			delete GAME;
			GAME = nullptr;
			Menu::openMenu();
		}
	}
}

void Game::create() {
	if (GAME == nullptr)
		GAME = new Game();
	GAME->show();
	Connection::sendPacket(PACKETPLAYINPLAYERSPAWN);
}

QSet<int> Game::getKeys() { return GAME->keys; }

QSet<Entity*> Game::getEntities() { return GAME->entities; }

Player* Game::getPlayer() { return GAME->player; }

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
	//	if (GAME->onlinePlayers.contains(user))
	GAME->onlinePlayers[user]->setPos(loc);
}

void Game::removeOnlinePlayer(const QString& user) {
	Player* player = GAME->onlinePlayers.take(user);
	if (player != nullptr)
		player->deleteLater();
}

void Game::addOnlinePlayer(PlayerType type, const QString& user) {
	Player* player = new Player(type, QPointF(0, 0), user);
	player->setOpacity(0.25);
	player->hitbox.hide();
	GAME->onlinePlayers.insert(user, player);
}
