#include "game.h"
#include <QKeyEvent>
#include "connection.h"
#include "entity.h"
#include "entityplayer.h"
#include "menu.h"
#include "packet.h"
#include "texture.h"
#include "user.h"

Game* Game::GAME = nullptr;

Game::Game(void)
    : QGraphicsView(),
      scene(0, 0, 900, 720),
      playableArea(-272, -340, 544, 680),
      background1(Texture::BACKGROUND, &playableArea),
      background2(Texture::BACKGROUND, &playableArea),
      dead("Game Over", &playableArea),
      menuButton("Return to Menu"),
      paused(false),
      age(0) {
  GAME = this;
  setScene(&scene);

  setInteractive(false);
  setViewport(&openGL);

  screen.setPixmap(Texture::BACKGROUNDTEMP);
  screen.setZValue(Texture::BACKGROUNDTEMP.zValue);
  scene.addItem(&screen);

  playableArea.setPos(40 + playableArea.boundingRect().width() / 2,
                      20 + playableArea.boundingRect().height() / 2);
  scene.addItem(&playableArea);

  background1.setPos({0, -340});
  background1.setOffset(-background1.boundingRect().center());
  background2.setPos({0, 340});
  background2.setOffset(-background2.boundingRect().center());

  popup.setLayout(&popupLayout);
  popup.setModal(true);
  popupLayout.addWidget(&popupText, 1, 1, 1, -1);
  popupLayout.addWidget(&menuButton, 2, 1, 1, -1);
  connect(&menuButton, &QPushButton::clicked, [this]() {
    Menu::openMenu();
    close();
    delete this;
  });

  dead.setBrush(Qt::red);
  dead.setScale(5);
  dead.setPos(-(dead.boundingRect().center().toPoint() * 5));
  dead.setZValue(10);
  dead.hide();

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
  age++;
  background1.moveBy(0, 1);
  background2.moveBy(0, 1);
  if (!background1.collidesWithItem(&playableArea))
    background1.moveBy(0, -1360);
  if (!background2.collidesWithItem(&playableArea))
    background2.moveBy(0, -1360);
  if (getPlayer() == nullptr) {
    if (age % 120 == 0)
      dead.show();
    else if (age % 120 == 60)
      dead.hide();
  }
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

QGraphicsRectItem& Game::getPlayableArea(void) {
  return GAME->playableArea;
}

QSet<int> Game::getKeys(void) {
  return GAME->keys;
}

Map<UID, Entity*> Game::getEntities(void) {
  return GAME->entities;
}

void Game::addEntity(Entity* entity) {
  queueEvent([entity]() { GAME->entities.insert({entity->id, entity}); });
}

void Game::queueEvent(std::function<void(void)> func) {
  if (GAME == nullptr)
    return;
  GAME->eventQueue.push_back(func);
}

EntityPlayer* Game::getPlayer(void) {
  if (GAME->entities.count(User::getUUID()))
    return dynamic_cast<EntityPlayer*>(GAME->entities[User::getUUID()]);
  return nullptr;
}
