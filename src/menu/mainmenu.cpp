#include "mainmenu.h"
#include <QGridLayout>
#include <QLabel>
#include "multiplayermenu.h"
#include "singleplayermenu.h"
#include "src/assets/music.h"
#include "src/assets/sfx.h"
#include "src/assets/texture.h"

MainMenu* MainMenu::MENU = nullptr;

MainMenu::MainMenu()
    : QDialog(),
      singleplayerButton("Singleplayer"),
      multiplayerButton("Multiplayer"),
      optionsButton("Scores"),
      quitButton("Quit") {
  QGridLayout* layout = new QGridLayout;
  setLayout(layout);

	QLabel* title = new QLabel;
	title->setPixmap(QPixmap(Textures::TITLE.texture));

	layout->addWidget(title, 1, 1, 1, -1);

	layout->addWidget(&singleplayerButton, 2, 1, 1, -1);
	connect(&singleplayerButton, &QPushButton::clicked, this,
          &MainMenu::openSingleplayerMenu);

	layout->addWidget(&multiplayerButton, 3, 1, 1, -1);
	connect(&multiplayerButton, &QPushButton::clicked, this,
          &MainMenu::openMultiplayerMenu);

	layout->addWidget(&optionsButton, 4, 1, 1, 1);
	connect(&optionsButton, &QPushButton::clicked, this,
					&MainMenu::openOptionsMenu);

	layout->addWidget(&quitButton, 4, 2, 1, 1);
  connect(&quitButton, &QPushButton::clicked, this, &MainMenu::close);

	setWindowFlags(Qt::FramelessWindowHint);

	Music::playSong(Music::MENU, 100);
}

void MainMenu::openMenu() {
  if (MENU == nullptr)
    MENU = new MainMenu();
  MENU->show();
}

void MainMenu::openSingleplayerMenu() {
  SingleplayerMenu::openMenu();
	SFX::playSound(SFX::SELECT_1, 1);
  close();
}

void MainMenu::openMultiplayerMenu() {
  MultiplayerMenu::openMenu();
	SFX::playSound(SFX::SELECT_1, 1);
  close();
}

void MainMenu::openOptionsMenu() {
	SFX::playSound(SFX::SELECT_1, 1);
}

void MainMenu::closeMenu() {
	if (MENU != nullptr)
		MENU->close();
}
