#include "mainmenu.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "singleplayermenu.h"

MainMenu::MainMenu() : QDialog() {
	QVBoxLayout* layout = new QVBoxLayout;
	setLayout(layout);
	setFixedSize(0, 0);

	QPushButton* singleplayerButton = new QPushButton("Singleplayer");
	layout->addWidget(singleplayerButton);
	connect(singleplayerButton, &QPushButton::clicked, this,
					&MainMenu::openSingleplayerMenu);

	QPushButton* multiplayerButton = new QPushButton("Multiplayer");
	layout->addWidget(multiplayerButton);
	connect(multiplayerButton, &QPushButton::clicked, this,
					&MainMenu::openMultiplayerMenu);

	QPushButton* optionsButton = new QPushButton("Options");
	layout->addWidget(optionsButton);
	connect(optionsButton, &QPushButton::clicked, this,
					&MainMenu::openOptionsMenu);

	QPushButton* quitButton = new QPushButton("Save and Quit");
	layout->addWidget(quitButton);
	connect(quitButton, &QPushButton::clicked, this, &MainMenu::close);
}

void MainMenu::openSingleplayerMenu() {
	SingleplayerMenu* menu = new SingleplayerMenu;
	menu->show();
	close();
}

void MainMenu::openMultiplayerMenu() {}

void MainMenu::openOptionsMenu() {}
