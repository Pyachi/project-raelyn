#include "lobbymenu.h"
#include <QGridLayout>
#include <QDir>
#include "src/network/connection.h"
#include "mainmenu.h"

LobbyMenu* LobbyMenu::MENU = nullptr;

LobbyMenu::LobbyMenu() : QDialog(), leaveButton("Leave"), startButton("Start") {
	MENU = this;

	QGridLayout* layout = new QGridLayout;
	setLayout(layout);
	setFixedSize(200, 120);

	layout->addWidget(&players, 1, 1, 2, 2);
	layout->addWidget(&startButton, 3, 1, 1, 1);
	layout->addWidget(&leaveButton, 3, 2, 1, 1);

	connect(&startButton, &QPushButton::clicked, this, &LobbyMenu::startGame);
	connect(&leaveButton, &QPushButton::clicked, this, &LobbyMenu::leaveLobby);
}

void LobbyMenu::setPlayers(const QStringList& players) {
	MENU->players.clear();
	foreach(QString string, players) { MENU->players.addItem(string); }
}

void LobbyMenu::leaveLobby() {
	Connection::disconnect();
	MainMenu::openMenu();
	close();
}

void LobbyMenu::startGame() {}

void LobbyMenu::openMenu() {
	if (MENU == nullptr)
		new LobbyMenu;
	MENU->show();
}
