#include "game.h"
#include "connection.h"
#include "entity.h"
#include "entityplayer.h"
#include "menu.h"
#include "packet.h"
#include "texture.h"
#include "user.h"
#include "font.h"
#include "sfx.h"
#include "collectable.h"

Game* Game::GAME = nullptr;

Game::Game(void)
    : QGraphicsView(),
      scene(0, 0, 900, 720),
			play(-272, -340, 544, 680),
			sidebar(Texture::BACKGROUNDTEMP),
			gameOver("Game Over", &play),
			background1(Texture::BACKGROUND, &play),
			background2(Texture::BACKGROUND, &play),
			background3(Texture::BACKGROUND2, &play),
			background4(Texture::BACKGROUND2, &play),
			highScore(&sidebar),
			score(&sidebar),
			powerDisplay(&sidebar),
			paused(false),
			age(0) {
  GAME = this;
  setScene(&scene);

  setInteractive(false);
  setViewport(&openGL);

	sidebar.setZValue(Texture::BACKGROUNDTEMP.zValue);
	scene.addItem(&sidebar);

	play.setPos(40 + play.boundingRect().width() / 2,
							20 + play.boundingRect().height() / 2);
	scene.addItem(&play);

  background1.setPos({0, -340});
  background1.setOffset(-background1.boundingRect().center());
  background2.setPos({0, 340});
  background2.setOffset(-background2.boundingRect().center());
  background3.setPos({0, -340});
  background3.setOffset(-background3.boundingRect().center());
  background4.setPos({0, 340});
  background4.setOffset(-background4.boundingRect().center());

	gameOver.setBrush(Qt::red);
	gameOver.setFont(Font::PRESSSTART);
	gameOver.setScale(3);
	gameOver.setPos(-(gameOver.boundingRect().center().toPoint() * 3));
	gameOver.setZValue(10);
	gameOver.hide();

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  adjustSize();
  setFixedSize(size() + QSize(2, 2));

	highScore.setText("00000000000");
	highScore.setBrush(Qt::white);
	highScore.setFont(Font::PRESSSTART);
	highScore.setPos({710, 116});

	score.setBrush(Qt::white);
	score.setFont(Font::PRESSSTART);
	score.setPos({710, 146});

	powerDisplay.setBrush(Qt::white);
	powerDisplay.setFont(Font::PRESSSTART);
	powerDisplay.setPos({710, 276});

	for (ushort i = 0; i < 7; i++) {
		healthDisplay.push_back(
				new QGraphicsPixmapItem(Texture::S_HEALTH_D, &sidebar));
		healthDisplay.at(i)->setPos({static_cast<double>(710 + (i * 25)), 195});
		bombsDisplay.push_back(
				new QGraphicsPixmapItem(Texture::S_BOMB_D, &sidebar));
		bombsDisplay.at(i)->setPos({static_cast<double>(710 + (i * 25)), 220});
	}

	for (ushort i = 0; i < health; i++)
		healthDisplay.at(i)->setPixmap(Texture::S_HEALTH);
	for (ushort i = 0; i < bombs; i++)
		bombsDisplay.at(i)->setPixmap(Texture::S_BOMB);

	timer.start(1000 / 60);
  connect(&timer, &QTimer::timeout, [this]() { this->tick(); });
}

void Game::tick(void) {
  if (paused)
    return;
	age++;
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
	if (!background1.collidesWithItem(&play))
    background1.moveBy(0, -1360);
	if (!background2.collidesWithItem(&play))
    background2.moveBy(0, -1360);
	if (!background3.collidesWithItem(&play))
    background3.moveBy(0, -1360);
	if (!background4.collidesWithItem(&play))
    background4.moveBy(0, -1360);
	//***************************************************************************
	// Event Scheduler
	for (std::function<void(Game&)> run : eventQueue)
		run(*this);
	eventQueue.clear();
	if (timedEventQueue.count(0))
		eventQueue = timedEventQueue.at(0);
	timedEventQueue.erase(0);
	Map<ushort, List<std::function<void(Game&)> > > timedEvents = timedEventQueue;
	timedEventQueue.clear();
	for (auto event : timedEvents)
		timedEventQueue.insert({event.first - 1, event.second});
	//***************************************************************************
	// Sidebar Display
	score.setText(QString::number(User::getScore()).rightJustified(11, '0'));
	if (playerAlive()) {
		powerDisplay.setText(QString::number(getPlayer()->level) + "." +
												 QString::number(power).rightJustified(2, '0') +
												 " / 4.00");
	} else {
		powerDisplay.setText("0.00 / 4.00");
	}
	//***************************************************************************
	// Game Over Display
	if (!playerAlive()) {
		if (age % 120 == 0) {
			gameOver.show();
		} else if (age % 120 == 60) {
			gameOver.hide();
		}
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

/* Creates game if one doesn't yet exist,
 * then opens it to the player
 */
void Game::create(void) {
  if (GAME == nullptr)
    GAME = new Game();
  GAME->show();
	Connection::sendPacket({PACKETPLAYINPLAYERSPAWN,
													QStringList() << QString::number(Character::valueOf(
																							 User::getCharacter()))});
}
/* Returns true if client player is alive, false otherwise
 */
bool Game::playerAlive(void) {
	return GAME == nullptr ? false : GAME->entities.count(User::getUID());
}

/* Returns one of three things, in order:
 * 1. The client player if alive
 * 2. An alive online player if any
 * 3. nullptr
 */
EntityPlayer* Game::getPlayer(void) {
	if (GAME == nullptr)
		return nullptr;
	if (playerAlive())
		return dynamic_cast<EntityPlayer*>(GAME->entities.at(User::getUID()));
	for (auto entity : GAME->entities)
		if (entity.second->type == ONLINEPLAYER)
			return dynamic_cast<EntityPlayer*>(entity.second);
	return nullptr;
}

/* Adds given entity to map
 */
void Game::addEntity(Entity* entity) {
	if (GAME == nullptr) {
		qDebug() << "ERROR: Attempted to add entity before Game exists!";
		return;
	}
	queueEvent(
			{[entity](Game& game) { game.entities.insert({entity->id, entity}); }});
}

/* Queues a task for the game to run after a given time.
 * If given time is 0, will run immediately without interrupting
 * the core game loop.
 */
void Game::queueEvent(std::function<void(Game&)> func, ushort time) {
	if (GAME == nullptr) {
		qDebug() << "ERROR: Attempted to queue event before Game exists!";
		return;
	}
	if (time == 0)
		GAME->eventQueue.push_back(func);
	else if (GAME->timedEventQueue.count(time))
		GAME->timedEventQueue[time].emplace_back(func);
	else
		GAME->timedEventQueue.insert({time, {func}});
}

/* Pauses the game
 */
void Game::pause(void) {
	if (GAME == nullptr) {
		qDebug() << "ERROR: Attempted to pause before Game exists!";
		return;
	}
	GAME->paused = true;
}

void Game::takeDamage(void) {
	if (GAME == nullptr || !playerAlive()) {
		qDebug() << "ERROR: Attempted to take damage at invalid time!";
		return;
	}
	GAME->health--;
	GAME->healthDisplay.at(GAME->health)->setPixmap(Texture::S_HEALTH_D);
	for (int i = 0; i < ((getPlayer()->level - 1) * 75) + GAME->power; i++)
		Collectable::POWER.spawn(getPlayer()->pos(), 50, 5);
	GAME->power = 0;
	if (GAME->health == 0) {
		SFX::EXPL_SUPERHEAVY1.play();
		getPlayer()->deleteLater();
		Connection::sendPacket(PACKETPLAYINPLAYERDEATH);
	} else {
		SFX::HIT1.play();
		Connection::sendPacket(PACKETPLAYINTAKEDAMAGE);
	}
}

void Game::gainHealth(void) {
	if (GAME == nullptr || !playerAlive()) {
		qDebug() << "ERROR: Attempted to gain health at invalid time!";
		return;
	}
	if (GAME->health == 7) {
		User::addScore(200000);
		return;
	}
	GAME->healthDisplay.at(GAME->health)->setPixmap(Texture::S_HEALTH);
	GAME->health++;
}

void Game::gainBomb(void) {
	if (GAME == nullptr || !playerAlive()) {
		qDebug() << "ERROR: Attempted to gain bombs at invalid time!";
		return;
	}
	if (GAME->bombs == 7) {
		User::addScore(100000);
		return;
	}
	GAME->bombsDisplay.at(GAME->bombs)->setPixmap(Texture::S_BOMB);
	GAME->bombs++;
}

void Game::gainPower(void) {
	if (GAME == nullptr || !playerAlive()) {
		qDebug() << "ERROR: Attempted to gain power at invalid time!";
		return;
	}
	if (getPlayer()->level == 4) {
		User::addScore(500);
		return;
	}
	GAME->power++;
	if (GAME->power == 100) {
		GAME->power = 0;
		getPlayer()->level++;
		SFX::POWERUP1.play();
		Connection::sendPacket(PACKETPLAYINLEVELUP);
	}
}

/* Cleanly deletes all remaining entities when game is closed
 */
Game::~Game(void) {
	GAME = nullptr;
	for (auto entity : entities) {
		if (entity.second->readyToDelete()) {
			entities.erase(entity.second->id);
			scene.removeItem(entity.second);
			delete entity.second;
		}
	}
}
