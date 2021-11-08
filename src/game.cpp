#include "game.h"
#include "menu.h"
#include "src/ai/enemyai.h"
#include "src/ai/playerai.h"
#include "src/assets/texture.h"
#include "src/entity/player.h"
#include "src/network/connection.h"
#include "src/network/user.h"
#include "src/network/packet.h"
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

	new Player(PYACHI, User::getName(), User::getUUID());
}

void Game::tick() {
	for (Entity* entity : entities.values()) {
		entity->tick();
	}
	while (!eventQueue.empty()) {
		eventQueue.front()();
		eventQueue.pop_front();
	}
	foreach(Entity * entity, entities.values()) {
		if (entity->readyToDelete()) {
			entities.remove(entity->id);
			scene.removeItem(entity);
		}
	}
}

void Game::create() {
	if (GAME == nullptr)
		GAME = new Game();
	GAME->show();
	Connection::sendPacket(
			{PACKETPLAYINPLAYERSPAWN, QStringList() << QString::number(PYACHI)});
}

QSet<int> Game::getKeys() { return GAME->keys; }

QMap<UUID, Entity*> Game::getEntities() { return GAME->entities; }

void Game::keyPressEvent(QKeyEvent* e) {
	keys.insert(e->key());
	QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent* e) {
	keys.remove(e->key());
	QGraphicsView::keyReleaseEvent(e);
}

QGraphicsPixmapItem& Game::getPlayableArea() { return GAME->playableArea; }

void Game::addEntity(Entity* entity) {
	GAME->entities.insert(entity->id, entity);
}

void Game::queueEvent(std::function<void(void)> func) {
	GAME->eventQueue.push_back(func);
}

Player* Game::getPlayer() {
	return dynamic_cast<Player*>(GAME->entities[User::getUUID()]);
}
