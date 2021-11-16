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
      background3(Texture::BACKGROUND2, &playableArea),
      background4(Texture::BACKGROUND2, &playableArea),
      dead("Game Over", &playableArea),
      menuButton("Return to Menu"),
      points(&screen),
      power(&screen),
			paused(false) {
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
  background3.setPos({0, -340});
  background3.setOffset(-background3.boundingRect().center());
  background4.setPos({0, 340});
  background4.setOffset(-background4.boundingRect().center());

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

  points.setBrush(Qt::white);
  points.setFont(QFont("Arial", 18));
  points.setPos({710, 139});

  power.setBrush(Qt::white);
  power.setFont(QFont("Arial", 18));
  power.setPos({710, 269});

  timer.start(1000 / 60);
  connect(&timer, &QTimer::timeout, [this]() { this->tick(); });
}

void Game::tick(void) {
  if (paused)
    return;
	//***************************************************************************
	// Entity Ticking
	for (auto entity : entities)
		entity.second->tick();
	//***************************************************************************
	// Background Animation
  background1.moveBy(0, 1);
  background2.moveBy(0, 1);
	background3.moveBy(0, 4);
	background4.moveBy(0, 4);
  if (!background1.collidesWithItem(&playableArea))
    background1.moveBy(0, -1360);
  if (!background2.collidesWithItem(&playableArea))
    background2.moveBy(0, -1360);
  if (!background3.collidesWithItem(&playableArea))
    background3.moveBy(0, -1360);
  if (!background4.collidesWithItem(&playableArea))
    background4.moveBy(0, -1360);
	//***************************************************************************
	// Event Scheduler
	for (std::function<void(Game&)> run : eventQueue)
		run(*this);
	eventQueue.clear();
	if (timedEventQueue.count(0))
		eventQueue = timedEventQueue.at(0);
	timedEventQueue.erase(0);
	Map<int, List<std::function<void(Game&)> > > timedEvents = timedEventQueue;
	timedEventQueue.clear();
	for (auto event : timedEvents)
		timedEventQueue.insert({event.first - 1, event.second});
	//***************************************************************************
	// Sidebar Display
	if (isPlayerAlive()) {
    power.setText(QString::number(getPlayer()->level) + "." +
                  QString::number(getPlayer()->power).rightJustified(2, '0') +
                  " / 4.00");
		points.setText(
				QString::number(User::getCurrentScore()).rightJustified(12, '0'));
	}
	//***************************************************************************
	// Entity Deletion
	Map<UID, Entity*> toDelete = entities;
	for (auto entity : toDelete) {
		if (entity.second->readyToDelete()) {
			entities.erase(entity.second->id);
			scene.removeItem(entity.second);
			delete entity.second;
		}
	}
	//***************************************************************************
}

void Game::create(void) {
  if (GAME == nullptr)
    GAME = new Game();
  GAME->show();
	Connection::sendPacket({PACKETPLAYINPLAYERSPAWN,
													QStringList() << QString::number(Character::valueOf(
																							 User::getCharacter()))});
}

EntityPlayer* Game::getPlayer(void) {
	if (GAME->entities.count(User::getUID()))
		return dynamic_cast<EntityPlayer*>(GAME->entities[User::getUID()]);
	else {
		EntityPlayer* player = nullptr;
		for (auto entity : GAME->entities) {
			if (entity.second->type == ONLINEPLAYER)
				player = dynamic_cast<EntityPlayer*>(entity.second);
		}
		return player;
	}
}

Game::~Game(void) {
	GAME = nullptr;
	foreach(auto entity, entities) {
		entities.erase(entity.second->id);
		scene.removeItem(entity.second);
		delete entity.second;
	}
}
