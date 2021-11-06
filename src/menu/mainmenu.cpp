#include "mainmenu.h"
#include <QGridLayout>
#include "multiplayermenu.h"
#include "singleplayermenu.h"
#include "src/assets/music.h"
#include "src/assets/sfx.h"

MainMenu* MainMenu::MENU = nullptr;

MainMenu::MainMenu()
    : QDialog(),
      singleplayerButton("Singleplayer"),
      multiplayerButton("Multiplayer"),
      optionsButton("Scores"),
      quitButton("Quit") {
  QGridLayout* layout = new QGridLayout;
  setLayout(layout);
  setFixedSize(200, 120);

  layout->addWidget(&singleplayerButton, 1, 1, 1, -1);
	connect(&singleplayerButton,
					&QPushButton::clicked,
					this,
          &MainMenu::openSingleplayerMenu);

  layout->addWidget(&multiplayerButton, 2, 1, 1, -1);
	connect(&multiplayerButton,
					&QPushButton::clicked,
					this,
          &MainMenu::openMultiplayerMenu);

  layout->addWidget(&optionsButton, 3, 1, 1, 1);
	connect(
			&optionsButton, &QPushButton::clicked, this, &MainMenu::openOptionsMenu);

  layout->addWidget(&quitButton, 3, 2, 1, 1);
  connect(&quitButton, &QPushButton::clicked, this, &MainMenu::close);

	Music::playSong(Music::MENU, 100);
}

void MainMenu::openMenu() {
  if (MENU == nullptr)
    MENU = new MainMenu();
  MENU->show();
}

void MainMenu::openSingleplayerMenu() {
  SingleplayerMenu::openMenu();
	SFX::playSound(SFX::SELECT_1, 0.1);
  close();
}

void MainMenu::openMultiplayerMenu() {
  MultiplayerMenu::openMenu();
	SFX::playSound(SFX::SELECT_1, 0.1);
  close();
}

void MainMenu::openOptionsMenu() { SFX::playSound(SFX::SELECT_1, 0.1); }

void MainMenu::closeMenu() {
	if (MENU != nullptr)
		MENU->close();
}
