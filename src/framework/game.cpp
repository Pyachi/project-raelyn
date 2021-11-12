#include "game.h"
#include <QKeyEvent>
#include "menu.h"
#include "src/ai/enemy.h"
#include "src/ai/player.h"
#include "src/assets/texture.h"
#include "src/entity/entityplayer.h"
#include "src/framework/user.h"
#include "src/network/connection.h"
#include "src/network/packet.h"

Game* Game::GAME = nullptr;

Game::Game(void)
    : QGraphicsView(),
      scene(0, 0, gameWidth, gameHeight),
      menuButton("Return to Menu"),
      paused(false) {
  GAME = this;
  setScene(&scene);

  setInteractive(false);
  setViewport(&openGL);

  QPixmap backgroundPixmap(
      QString::fromStdString(Textures::getTexture(TEXTURE_BACKGROUNDTEMP)));
  background.setPixmap(backgroundPixmap);
  background.setZValue(Textures::getZValue(TEXTURE_BACKGROUNDTEMP));
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

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  adjustSize();
	setFixedSize(size() + QSize(2, 2));

  timer.start(1000 / 60);
  connect(&timer, &QTimer::timeout, [this]() { this->tick(); });
}

Game::~Game(void) {
  foreach (auto entity, entities) {
    GAME = nullptr;
    entities.erase(entity.second->id);
    scene.removeItem(entity.second);
    delete entity.second;
  }
}

void Game::tick(void) {
  if (paused)
    return;
  for (auto entity : entities) {
    entity.second->tick();
  }
  while (!eventQueue.empty()) {
    eventQueue.front()();
    eventQueue.pop_front();
  }
  foreach (auto entity, entities) {
    if (entity.second->readyToDelete()) {
      entities.erase(entity.second->id);
      scene.removeItem(entity.second);
      delete entity.second;
    }
  }
}

void Game::create(void) {
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

QGraphicsPixmapItem& Game::getPlayableArea(void) {
  return GAME->playableArea;
}

QSet<int> Game::getKeys(void) {
  return GAME->keys;
}

Map<UID, Entity*> Game::getEntities(void) {
  return GAME->entities;
}

void Game::addEntity(Entity* entity) {
  GAME->entities.insert({entity->id, entity});
}

void Game::queueEvent(std::function<void(void)> func) {
  if (GAME == nullptr)
    return;
  GAME->eventQueue.push_back(func);
}

EntityPlayer* Game::getPlayer(void) {
  return dynamic_cast<EntityPlayer*>(GAME->entities[User::getUUID()]);
}
