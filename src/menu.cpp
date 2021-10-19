#include "menu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "game.h"

Menu::Menu() : QDialog() {
	setFixedSize(0,0);
	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);
	QPushButton* singleplayerButton = new QPushButton("Singleplayer");
	layout->addWidget(singleplayerButton);
	connect(singleplayerButton, &QPushButton::clicked, this, &Menu::singleplayer);
	QPushButton* multiplayerButton = new QPushButton("Multiplayer");
	layout->addWidget(multiplayerButton);
	connect(multiplayerButton, &QPushButton::clicked, this, &Menu::multiplayer);
	QPushButton* optionsButton = new QPushButton("Options");
	layout->addWidget(optionsButton);
	connect(optionsButton, &QPushButton::clicked, this, &Menu::options);
	QPushButton* quitButton = new QPushButton("Save and Quit");
	layout->addWidget(quitButton);
	connect(quitButton, &QPushButton::clicked, this, &Menu::quit);
}

void Menu::singleplayer() {
	Game* game = new Game;
	game->show();
	close();
}

void Menu::multiplayer() {}

void Menu::options() {}

void Menu::quit() { close(); }
