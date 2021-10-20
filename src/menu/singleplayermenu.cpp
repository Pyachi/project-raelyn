#include "singleplayermenu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "mainmenu.h"
#include "src/game.h"

SingleplayerMenu::SingleplayerMenu() {
	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);
	setFixedSize(0, 0);

	QPushButton* characterButton = new QPushButton("Character: Pyachi");
	layout->addWidget(characterButton);
	connect(characterButton, &QPushButton::clicked, this,
					&SingleplayerMenu::changeCharacter);

	QPushButton* difficultyButton = new QPushButton("Difficulty: Normal");
	layout->addWidget(difficultyButton);
	connect(difficultyButton, &QPushButton::clicked, this,
					&SingleplayerMenu::changeDifficulty);

	QPushButton* startButton = new QPushButton("Start Game");
	layout->addWidget(startButton);
	connect(startButton, &QPushButton::clicked, this,
					&SingleplayerMenu::startGame);

	QPushButton* quitButton = new QPushButton("Return to Menu");
	layout->addWidget(quitButton);
	connect(quitButton, &QPushButton::clicked, this,
					&SingleplayerMenu::returnToMenu);
}

void SingleplayerMenu::changeCharacter() {}

void SingleplayerMenu::changeDifficulty() {}

void SingleplayerMenu::startGame() {
	Game* game = new Game;
	game->show();
	close();
}

void SingleplayerMenu::returnToMenu() {
	MainMenu* menu = new MainMenu;
	menu->show();
	close();
}
