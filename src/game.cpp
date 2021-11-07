#include "game.h"
#include "src/ai/playerai.h"
#include "src/ai/enemyai.h"
#include "src/assets/texture.h"
#include "src/network/user.h"
#include "src/network/connection.h"
#include "src/entity/player.h"
#include "menu.h"
#include <QKeyEvent>

Game* Game::GAME = nullptr;

Game::Game() : QGraphicsView(), scene(0, 0, gameWidth, gameHeight) {
	GAME = this;
	setScene(&scene);

	setInteractive(false);
	setViewport(&openGL);

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

	timer.start(1000 / 60);
	connect(&timer, &QTimer::timeout, this, &Game::tick);

	player = new Player(PYACHI, User::getName());

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
	player->tick();
	if (player->readyToDelete()) {
		close();
		delete GAME;
		GAME = nullptr;
		Menu::openMenu();
	}
	if (!onlineQueue.empty()) {
		onlineQueue.front()();
		onlineQueue.pop_front();
	}
}

void Game::create() {
	if (GAME == nullptr)
		GAME = new Game();
	GAME->show();
	Connection::sendPacket(PACKETPLAYINPLAYERSPAWN);
}

QSet<int> Game::getKeys() { return GAME->keys; }

List<Entity*> Game::getEntities() { return GAME->entities; }

Player* Game::getPlayer() { return GAME->player; }

void Game::keyPressEvent(QKeyEvent* e) {
	keys.insert(e->key());
	QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent* e) {
	keys.remove(e->key());
	QGraphicsView::keyReleaseEvent(e);
}

QGraphicsPixmapItem& Game::getPlayableArea() { return GAME->playableArea; }

void Game::addEntity(Entity* entity) { GAME->entities.push_back(entity); }

void Game::updatePlayerLocation(const QString& user, const QPointF& loc) {
	GAME->onlineQueue.push_back([user, loc]() {
		GAME->onlinePlayers.at(user)->setPos(loc);
	});
}

void Game::removeOnlinePlayer(const QString& user) {
	GAME->onlinePlayers.at(user)->deleteLater();
	GAME->onlinePlayers.erase(user);
}

void Game::addOnlinePlayer(PlayerType type, const QString& user) {
	Player* player = new Player(type, user);
	player->setOpacity(0.25);
	player->hitbox.hide();
	GAME->onlinePlayers.insert(std::pair<QString, Player*>(user, player));
}