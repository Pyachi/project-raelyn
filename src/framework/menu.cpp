#include "menu.h"
#include "src/assets/music.h"
#include "src/assets/sfx.h"
#include "src/assets/texture.h"
#include "src/network/connection.h"
#include "src/network/packet.h"
#include "src/network/server.h"
#include "src/network/user.h"

Menu* Menu::MENU = nullptr;

Menu::Menu()
    : QDialog(),
			singleplayer("Singleplayer"),
			multiplayer("Multiplayer"),
			options("Options"),
			quit("Quit"),
			playerSingle("Character: Pyachi"),
			start("Start Game"),
			backSingleplayer("Return to Menu"),
			ipForm("127.0.0.1"),
			ipValidator(QRegExp("[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}")),
			portForm("1337"),
			portValidator(QRegExp(
					"^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|"
					"655[0-2][0-9]|6553[0-5])$")),
			host("Host"),
			join("Join"),
			backMultiplayer("Return to Menu"),
			soundLabel("Sound Volume:"),
			soundSlider(Qt::Horizontal),
			musicLabel("Music Volume:"),
			musicSlider(Qt::Horizontal),
			backOptions("Return to Menu"),
			playerCount("Players Connected: 0"),
			backServer("Return to Menu"),
			playerLobby("Character: Pyachi"),
			startLobby("Start Game"),
			backLobby("Return to Menu") {
	setLayout(&layout);
	setWindowFlags(Qt::FramelessWindowHint);

	setFixedSize(0, 0);

	title.setPixmap(QPixmap(Texture::get(TITLE).texture));
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
	singleplayerLayout.addWidget(&playerSingle, 1, 1, 1, -1);
	singleplayerLayout.addWidget(&start, 2, 1, 1, -1);
	singleplayerLayout.addWidget(&backSingleplayer, 3, 1, 1, -1);
	connect(&playerSingle, &QPushButton::clicked, this, &Menu::changeCharacter);
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
	ipForm.setValidator(&ipValidator);
	portForm.setValidator(&portValidator);

	optionsMenu.setLayout(&optionsLayout);
	optionsLayout.addWidget(&soundLabel, 1, 1, 1, -1);
	optionsLayout.addWidget(&soundSlider, 2, 1, 1, -1);
	soundSlider.setValue(99);
	optionsLayout.addWidget(&musicLabel, 3, 1, 1, -1);
	optionsLayout.addWidget(&musicSlider, 4, 1, 1, -1);
	musicSlider.setValue(99);
	optionsLayout.addWidget(&backOptions, 5, 1, 1, -1);
	connect(&soundSlider, &QSlider::valueChanged, [this]() {
		SFX::volume = this->soundSlider.value() / 100.0;
		SFX::playSound(COLLECT_1);
	});
	connect(&musicSlider, &QSlider::valueChanged,
					[this]() { Music::changeVolume(this->musicSlider.value()); });
	connect(&backOptions, &QPushButton::clicked, this, &Menu::returnToMenu);

	serverMenu.setLayout(&serverLayout);
	serverLayout.addWidget(&connectionInfo, 1, 1, 1, -1);
	serverLayout.addWidget(&playerCount, 2, 1, 1, -1);
	serverLayout.addWidget(&backServer, 3, 1, 1, -1);
	connect(&backServer, &QPushButton::clicked, this, &Menu::returnToMenu);

	lobbyMenu.setLayout(&lobbyLayout);
	lobbyLayout.addWidget(&players, 1, 1, 1, -1);
	lobbyLayout.addWidget(&playerLobby, 2, 1, 1, -1);
	lobbyLayout.addWidget(&startLobby, 3, 1, 1, -1);
	lobbyLayout.addWidget(&backLobby, 4, 1, 1, -1);
	connect(&playerLobby, &QPushButton::clicked, this, &Menu::changeCharacter);
	connect(&startLobby, &QPushButton::clicked, this, &Menu::startGame);
	connect(&backLobby, &QPushButton::clicked, this, &Menu::returnToMenu);
}

void Menu::openMenu() {
	if (MENU == nullptr)
		MENU = new Menu();
	MENU->show();
	MENU->returnToMenu();
	Music::playSong(Song::MENU);
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
	for (QString string : list)
		MENU->players.addItem(string);
}

void Menu::openSingleplayer() {
	mainMenu.hide();
	singleplayerMenu.show();
	SFX::playSound(SELECT_1, 1);
}

void Menu::openMultiplayer() {
	mainMenu.hide();
	lobbyMenu.hide();
	multiplayerMenu.show();
	SFX::playSound(SELECT_1, 1);
}

void Menu::openOptions() {
	mainMenu.hide();
	optionsMenu.show();
	SFX::playSound(SELECT_1, 1);
}

void Menu::quitGame() {
	close();
}

void Menu::startGame() {
	if (!Connection::exists()) {
		if (!Server::create(1337) || !Connection::create("127.0.0.1", 1337)) {
			SFX::playSound(SELECT_2, 1);
			return;
		}
	}
	Connection::sendPacket(PACKETPLAYINSTARTGAME);
}

void Menu::returnToMenu() {
	if (serverMenu.isVisible())
		Music::playSong(Song::MENU);
	Connection::disconnect();
	Server::disconnect();
	mainMenu.show();
	singleplayerMenu.hide();
	multiplayerMenu.hide();
	optionsMenu.hide();
	lobbyMenu.hide();
	serverMenu.hide();
	SFX::playSound(SELECT_2, 1);
}

void Menu::hostServer() {
	if (!Server::create(portForm.text().toUShort())) {
		SFX::playSound(SELECT_2, 1);
		return;
	}
	connectionInfo.setText(User::getIp() + ":" +
												 QString::number(Server::getPort()));
	multiplayerMenu.hide();
	serverMenu.show();
	SFX::playSound(SELECT_1, 1);
	Music::stopSong();
}

void Menu::joinServer() {
	if (Connection::create(ipForm.text(), portForm.text().toUShort())) {
		lobbyMenu.show();
		multiplayerMenu.hide();
		Connection::sendPacket(PACKETPLAYINUPDATELOBBY);
		SFX::playSound(SELECT_1, 1);
	} else
		SFX::playSound(SELECT_2, 1);
}

void Menu::changeCharacter() {
	switch (User::character) {
		case PYACHI:
			User::character = AERON;
			playerSingle.setText("Character: Aeron");
			playerLobby.setText("Character: Aeron");
			break;
		case AERON:
			User::character = DAESCH;
			playerSingle.setText("Character: Daesch");
			playerLobby.setText("Character: Daesch");
			break;
		case DAESCH:
			User::character = ANEKHANDA;
			playerSingle.setText("Character: Anekhanda");
			playerLobby.setText("Character: Anekhanda");
			break;
		case ANEKHANDA:
			User::character = PYACHI;
			playerSingle.setText("Character: Pyachi");
			playerLobby.setText("Character: Pyachi");
			break;
	}
}
