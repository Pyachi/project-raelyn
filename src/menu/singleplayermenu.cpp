#include "singleplayermenu.h"
#include <QGridLayout>
#include "mainmenu.h"
#include "src/assets/sfx.h"
#include "src/entity/player.h"
#include "src/game/game.h"
#include "src/network/connection.h"
#include "src/network/server.h"

SingleplayerMenu* SingleplayerMenu::MENU = nullptr;

SingleplayerMenu::SingleplayerMenu()
    : QDialog(),
      characterButton("Character: Pyachi"),
      difficultyButton("Difficulty: Normal"),
      startButton("Start"),
      quitButton("Back") {
  QGridLayout* layout = new QGridLayout;
  setLayout(layout);
  setFixedSize(200, 120);

  layout->addWidget(&characterButton, 1, 1, 1, -1);
	connect(&characterButton, &QPushButton::clicked, this,
          &SingleplayerMenu::changeCharacter);

  layout->addWidget(&difficultyButton, 2, 1, 1, -1);
	connect(&difficultyButton, &QPushButton::clicked, this,
          &SingleplayerMenu::changeDifficulty);

  layout->addWidget(&startButton, 3, 2, 1, 1);
	connect(&startButton, &QPushButton::clicked, this,
					&SingleplayerMenu::startGame);

  layout->addWidget(&quitButton, 3, 1, 1, 1);
	connect(&quitButton, &QPushButton::clicked, this,
          &SingleplayerMenu::returnToMenu);

	setWindowFlags(Qt::FramelessWindowHint);
}

void SingleplayerMenu::openMenu() {
  if (MENU == nullptr)
    MENU = new SingleplayerMenu();
  MENU->show();
}

void SingleplayerMenu::changeCharacter() {
	SFX::playSound(SFX::SELECT_1, 1);
  if (characterButton.text().contains("Pyachi"))
    characterButton.setText("Character: Aeron");
  else
    characterButton.setText("Character: Pyachi");
}

void SingleplayerMenu::changeDifficulty() {
	SFX::playSound(SFX::SELECT_1, 1);
  if (difficultyButton.text().contains("Normal"))
    difficultyButton.setText("Difficulty: Hard");
  else
    difficultyButton.setText("Difficulty: Normal");
}

void SingleplayerMenu::startGame() {
	if (!Server::create(1337))
		return;
	if (!Connection::create("127.0.0.1", 1337))
		return;
	Connection::sendPacket(PACKETPLAYINSTARTGAME);
}

void SingleplayerMenu::returnToMenu() {
	SFX::playSound(SFX::SELECT_2, 1);
  MainMenu::openMenu();
  close();
}

void SingleplayerMenu::closeMenu() {
	if (MENU != nullptr)
		MENU->close();
}
