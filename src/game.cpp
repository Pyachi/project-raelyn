#include "game.h"
#include <QKeyEvent>
#include "menu.h"
#include "src/ai/enemyai.h"
#include "src/ai/playerai.h"
#include "src/assets/texture.h"
#include "src/entity/player.h"
#include "src/network/connection.h"
#include "src/network/user.h"

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
	while (!eventQueue.empty()) {
		eventQueue.front()();
		eventQueue.pop_front();
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

void Game::queueEvent(std::function<void(void)> func) {
	GAME->eventQueue.push_back(func);
}
