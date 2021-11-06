#include "menu.h"
#include "src/assets/music.h"
#include "src/assets/sfx.h"
#include "src/assets/texture.h"
#include "src/network/server.h"
#include "src/network/connection.h"
#include "src/network/user.h"

Menu* Menu::MENU = nullptr;

Menu::Menu()
    : QDialog(),
			singleplayer("Singleplayer"),
			multiplayer("Multiplayer"),
			options("Options"),
			quit("Quit"),
			player("Character: Pyachi"),
			start("Start Game"),
			backSingleplayer("Return to Menu"),
			ipForm("127.0.0.1"),
			portForm("1337"),
			host("Host"),
			join("Join"),
			backMultiplayer("Return to Menu"),
			backOptions("Return to Menu"),
			playerCount("Players Connected: 0"),
			backServer("Return to Menu"),
			startLobby("Start Game"),
			backLobby("Return to Menu") {
	setLayout(&layout);
	setWindowFlags(Qt::FramelessWindowHint);

	title.setPixmap(QPixmap(Textures::TITLE.texture));
	layout.addWidget(&title, 1, 1, 1, -1);
	layout.addWidget(&mainMenu, 2, 1, 1, -1);
	layout.addWidget(&singleplayerMenu, 2, 1, 1, -1);
	layout.addWidget(&multiplayerMenu, 2, 1, 1, -1);
	layout.addWidget(&optionsMenu, 2, 1, 1, -1);
	layout.addWidget(&lobbyMenu, 2, 1, 1, -1);
	layout.addWidget(&serverMenu, 2, 1, 1, -1);

	singleplayerMenu.hide();
	multiplayerMenu.hide();
	optionsMenu.hide();
	lobbyMenu.hide();
	serverMenu.hide();

	mainMenu.setLayout(&mainLayout);
	mainLayout.addWidget(&singleplayer, 1, 1, 1, -1);
	mainLayout.addWidget(&multiplayer, 2, 1, 1, -1);
	mainLayout.addWidget(&options, 3, 1, 1, 1);
	mainLayout.addWidget(&quit, 3, 2, 1, 1);
	connect(&singleplayer, &QPushButton::clicked, this, &Menu::openSingleplayer);
	connect(&multiplayer, &QPushButton::clicked, this, &Menu::openMultiplayer);
	connect(&options, &QPushButton::clicked, this, &Menu::openOptions);
	connect(&quit, &QPushButton::clicked, this, &Menu::quitGame);

	singleplayerMenu.setLayout(&singleplayerLayout);
	singleplayerLayout.addWidget(&player, 1, 1, 1, -1);
	singleplayerLayout.addWidget(&start, 2, 1, 1, -1);
	singleplayerLayout.addWidget(&backSingleplayer, 3, 1, 1, -1);
	connect(&player, &QPushButton::clicked, this, &Menu::changeCharacter);
	connect(&start, &QPushButton::clicked, this, &Menu::startGame);
	connect(&backSingleplayer, &QPushButton::clicked, this, &Menu::returnToMenu);

	multiplayerMenu.setLayout(&multiplayerLayout);
	multiplayerLayout.addWidget(&ipForm, 1, 1, 1, 1);
	multiplayerLayout.addWidget(&portForm, 1, 2, 1, 1);
	multiplayerLayout.addWidget(&host, 2, 1, 1, 1);
	multiplayerLayout.addWidget(&join, 2, 2, 1, 1);
	multiplayerLayout.addWidget(&backMultiplayer, 3, 1, 1, -1);
	connect(&host, &QPushButton::clicked, this, &Menu::hostServer);
	connect(&join, &QPushButton::clicked, this, &Menu::joinServer);
	connect(&backMultiplayer, &QPushButton::clicked, this, &Menu::returnToMenu);

	optionsMenu.setLayout(&optionsLayout);
	optionsLayout.addWidget(&backOptions, 1, 1, 1, -1);
	connect(&backOptions, &QPushButton::clicked, this, &Menu::returnToMenu);

	serverMenu.setLayout(&serverLayout);
	serverLayout.addWidget(&connectionInfo, 1, 1, 1, -1);
	serverLayout.addWidget(&playerCount, 2, 1, 1, -1);
	serverLayout.addWidget(&backServer, 3, 1, 1, -1);
	connect(&backServer, &QPushButton::clicked, this, &Menu::returnToMenu);

	lobbyMenu.setLayout(&lobbyLayout);
	lobbyLayout.addWidget(&players, 1, 1, 1, -1);
	lobbyLayout.addWidget(&startLobby, 2, 1, 1, -1);
	lobbyLayout.addWidget(&backLobby, 3, 1, 1, -1);
	connect(&startLobby, &QPushButton::clicked, this, &Menu::startGame);
	connect(&backLobby, &QPushButton::clicked, this, &Menu::returnToMenu);

	Music::playSong(Music::MENU, 100);
}

void Menu::openMenu() {
	if (MENU == nullptr)
		MENU = new Menu();
	MENU->show();
}

void Menu::closeMenu() {
	if (MENU != nullptr)
		MENU->close();
}

void Menu::updatePlayerCount(int size) {
	MENU->playerCount.setText("Players Connected: " + QString::number(size));
}

void Menu::updatePlayerList(const QStringList& list) {
	MENU->players.clear();
	foreach(QString string, list) { MENU->players.addItem(string); }
}

void Menu::openSingleplayer() {
	mainMenu.hide();
	singleplayerMenu.show();
	SFX::playSound(SFX::SELECT_1, 1);
}

void Menu::openMultiplayer() {
	mainMenu.hide();
	multiplayerMenu.show();
	SFX::playSound(SFX::SELECT_1, 1);
}

void Menu::openOptions() {
	mainMenu.hide();
	optionsMenu.show();
	SFX::playSound(SFX::SELECT_1, 1);
}

void Menu::quitGame() { close(); }

void Menu::startGame() {
	if (!Connection::exists()) {
		if (!Server::create(1337) || !Connection::create("127.0.0.1", 1337)) {
			SFX::playSound(SFX::SELECT_2, 1);
			return;
		}
	}
	Connection::sendPacket(PACKETPLAYINSTARTGAME);
}

void Menu::returnToMenu() {
	Connection::disconnect();
	Server::disconnect();
	mainMenu.show();
	singleplayerMenu.hide();
	multiplayerMenu.hide();
	optionsMenu.hide();
	lobbyMenu.hide();
	serverMenu.hide();
	SFX::playSound(SFX::SELECT_2, 1);
}

void Menu::hostServer() {
	if (!Server::create(portForm.text().toUShort())) {
		SFX::playSound(SFX::SELECT_2, 1);
		return;
	}
	connectionInfo.setText(User::getIp() + ":" +
												 QString::number(Server::getPort()));
	multiplayerMenu.hide();
	serverMenu.show();
	SFX::playSound(SFX::SELECT_1, 1);
}

void Menu::joinServer() {
	if (Connection::create(ipForm.text(), portForm.text().toUShort())) {
		lobbyMenu.show();
		multiplayerMenu.hide();
		Connection::sendPacket(PACKETPLAYINUPDATELOBBY);
		SFX::playSound(SFX::SELECT_1, 1);
	} else
		SFX::playSound(SFX::SELECT_2, 1);
}

void Menu::changeCharacter() {}
