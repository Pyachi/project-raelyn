#include "game.h"
#include <QKeyEvent>
#include "menu.h"
#include "src/ai/enemy.h"
#include "src/ai/player.h"
#include "src/assets/texture.h"
#include "src/entity/entityplayer.h"
#include "src/network/connection.h"
#include "src/network/packet.h"
#include "src/network/user.h"

Game* Game::GAME = nullptr;

Game::Game()
		: QGraphicsView(),
			scene(0, 0, gameWidth, gameHeight),
			menuButton("Return to Menu"),
			paused(false) {
	GAME = this;
	setScene(&scene);

	setInteractive(false);
	setViewport(&openGL);

	QPixmap backgroundPixmap(Texture::get(BACKGROUND).texture);
	background.setPixmap(backgroundPixmap);
	background.setZValue(Texture::get(BACKGROUND).zValue);
	scene.addItem(&background);

	QPixmap playableAreaPixmap(gameHeight - (playBorder * 2),
														 gameHeight - (playBorder * 2));
	playableAreaPixmap.fill(Qt::darkRed);
	playableArea.setPixmap(playableAreaPixmap);
	playableArea.setOffset(-playableArea.boundingRect().center());
	playableArea.setPos(playBorder + playableArea.boundingRect().width() / 2,
											playBorder + playableArea.boundingRect().height() / 2);
	scene.addItem(&playableArea);

	popup.setLayout(&popupLayout);
	popup.setModal(true);
	popupLayout.addWidget(&popupText, 1, 1, 1, -1);
	popupLayout.addWidget(&menuButton, 2, 1, 1, -1);
	connect(&menuButton, &QPushButton::clicked, [this]() {
		Menu::openMenu();
		close();
		delete this;
	});

	setFixedSize(gameWidth + 2, gameHeight + 2);

	timer.start(1000 / 60);
	connect(&timer, &QTimer::timeout, [this]() { this->tick(); });
}

Game::~Game() {
	foreach (Entity* entity, entities.values()) {
		GAME = nullptr;
		entities.remove(entity->id);
		scene.removeItem(entity);
		delete entity;
	}
}

void Game::tick() {
	if (paused)
		return;
	for (Entity* entity : entities.values()) {
		entity->tick();
	}
	while (!eventQueue.empty()) {
		eventQueue.front()();
		eventQueue.pop_front();
	}
	foreach (Entity* entity, entities.values()) {
		if (entity->readyToDelete()) {
			entities.remove(entity->id);
			scene.removeItem(entity);
			delete entity;
		}
	}
}

void Game::create() {
	if (GAME == nullptr)
		GAME = new Game();
	GAME->show();
	Connection::sendPacket({PACKETPLAYINPLAYERSPAWN,
													QStringList() << QString::number(User::character)});
}

void Game::keyPressEvent(QKeyEvent* e) {
	keys.insert(e->key());
	QGraphicsView::keyPressEvent(e);
}

void Game::keyReleaseEvent(QKeyEvent* e) {
	keys.remove(e->key());
	QGraphicsView::keyReleaseEvent(e);
}

QGraphicsPixmapItem& Game::getPlayableArea() {
	return GAME->playableArea;
}

QSet<int> Game::getKeys() {
	return GAME->keys;
}

QMap<UUID, Entity*> Game::getEntities() {
	return GAME->entities;
}

void Game::addEntity(Entity* entity) {
	GAME->entities.insert(entity->id, entity);
}

void Game::queueEvent(std::function<void(void)> func) {
	GAME->eventQueue.push_back(func);
}

EntityPlayer* Game::getPlayer() {
	return dynamic_cast<EntityPlayer*>(GAME->entities[User::getUUID()]);
}
