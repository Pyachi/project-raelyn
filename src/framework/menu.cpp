#include "menu.h"
#include "connection.h"
#include "controls.h"
#include "music.h"
#include "packet.h"
#include "server.h"
#include "sfx.h"
#include "texture.h"
#include "user.h"

Menu* Menu::MENU = nullptr;

Menu::Menu(void)
    : QDialog(),
      singleplayer("Singleplayer"),
      multiplayer("Multiplayer"),
      options("Options"),
      quit("Quit"),
			playerSingle(User::getCharacter()),
      start("Start Game"),
      backSingleplayer("Return to Menu"),
      ipForm("127.0.0.1"),
      ipValidator(QRegExp("[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}")),
      portForm("1337"),
      portValidator(QRegExp(
          "^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|"
          "655[0-2][0-9]|6553[0-5])")),
      host("Host"),
      join("Join"),
      backMultiplayer("Return to Menu"),
      soundLabel("Sound Volume:"),
      soundSlider(Qt::Horizontal),
      musicLabel("Music Volume:"),
      musicSlider(Qt::Horizontal),
			keys(User::getControls()),
      backOptions("Return to Menu"),
      serverStatus("Status: In Lobby"),
      playerCount("Players Connected: 0"),
      backServer("Return to Menu"),
			playerLobby(User::getCharacter()),
			readyLobby("Ready Up ☐"),
      backLobby("Return to Menu") {
  setLayout(&layout);
  setWindowFlags(Qt::FramelessWindowHint);

  setFixedSize(0, 0);

  title.setPixmap(Texture::TITLETEMP);
  title.setAlignment(Qt::AlignHCenter);
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

  //************************************************************
  mainMenu.setLayout(&mainLayout);
  mainLayout.addWidget(&singleplayer, 1, 1, 1, -1);
  mainLayout.addWidget(&multiplayer, 2, 1, 1, -1);
  mainLayout.addWidget(&options, 3, 1, 1, 1);
  mainLayout.addWidget(&quit, 3, 2, 1, 1);
  connect(&singleplayer, &QPushButton::clicked, [this]() {
    mainMenu.hide();
    singleplayerMenu.show();
    adjustSize();
    SFX::SELECT1.play(25);
  });
  connect(&multiplayer, &QPushButton::clicked, [this]() {
    mainMenu.hide();
    multiplayerMenu.show();
    adjustSize();
    SFX::SELECT1.play(25);
  });
  connect(&options, &QPushButton::clicked, [this]() {
    mainMenu.hide();
    optionsMenu.show();
    adjustSize();
    SFX::SELECT1.play(25);
  });
	connect(&quit, &QPushButton::clicked, [this]() { close(); });
  //************************************************************
  singleplayerMenu.setLayout(&singleplayerLayout);
  singleplayerLayout.addWidget(&playerSingle, 1, 1, 1, -1);
  singleplayerLayout.addWidget(&start, 2, 1, 1, -1);
  singleplayerLayout.addWidget(&backSingleplayer, 3, 1, 1, -1);
  connect(&playerSingle, &QPushButton::clicked, [this]() {
		SFX::SELECT1.play(25);
    switch (Character::valueOf(User::getCharacter())) {
      case 0:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
        break;
      case 1:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
        break;
      case 2:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
        break;
      case 3:
        User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
        break;
    }
  });
  connect(&start, &QPushButton::clicked, []() {
    Server::create(0);
    Connection::create("127.0.0.1", Server::getPort());
		Connection::sendPacket(S_START);
  });
  connect(&backSingleplayer, &QPushButton::clicked, [this]() {
    singleplayerMenu.hide();
    mainMenu.show();
    adjustSize();
    SFX::SELECT2.play(25);
  });
  //************************************************************
  multiplayerMenu.setLayout(&multiplayerLayout);
  multiplayerLayout.addWidget(&ipForm, 1, 1, 1, 1);
  multiplayerLayout.addWidget(&portForm, 1, 2, 1, 1);
  multiplayerLayout.addWidget(&host, 2, 1, 1, 1);
  multiplayerLayout.addWidget(&join, 2, 2, 1, 1);
  multiplayerLayout.addWidget(&backMultiplayer, 3, 1, 1, -1);
  connect(&host, &QPushButton::clicked, [this]() {
    if (!Server::create(portForm.text().toUShort())) {
      SFX::SELECT2.play(25);
      return;
    }
    connectionInfo.setText(QString::fromStdString(User::getIP()) + ":" +
                           QString::number(Server::getPort()));
    multiplayerMenu.hide();
    serverMenu.show();
    adjustSize();
    SFX::SELECT1.play(25);
    Music::stop();
  });
  connect(&join, &QPushButton::clicked, [this]() {
    if (Connection::create(ipForm.text(), portForm.text().toUShort())) {
      lobbyMenu.show();
      multiplayerMenu.hide();
      adjustSize();
			Connection::sendPacket(S_JOIN);
    } else
      SFX::SELECT2.play(25);
  });
  connect(&backMultiplayer, &QPushButton::clicked, [this]() {
    multiplayerMenu.hide();
    mainMenu.show();
    adjustSize();
    SFX::SELECT2.play(25);
  });
  ipForm.setValidator(&ipValidator);
  portForm.setValidator(&portValidator);
  //************************************************************
  optionsMenu.setLayout(&optionsLayout);
  optionsLayout.addWidget(&soundLabel, 1, 1, 1, -1);
  optionsLayout.addWidget(&soundSlider, 2, 1, 1, -1);
  soundSlider.setMaximum(5);
  soundSlider.setValue(User::getSoundVol() / 20);
  optionsLayout.addWidget(&musicLabel, 3, 1, 1, -1);
  optionsLayout.addWidget(&musicSlider, 4, 1, 1, -1);
  musicSlider.setMaximum(5);
  musicSlider.setValue(User::getMusicVol() / 20);
  optionsLayout.addWidget(&keys, 5, 1, 1, -1);
  optionsLayout.addWidget(&backOptions, 6, 1, 1, -1);
  connect(&soundSlider, &QSlider::valueChanged, [this]() {
    User::setSoundVol(soundSlider.value() * 20);
    SFX::COLLECT2.play();
  });
	connect(&musicSlider, &QSlider::valueChanged, [this]() {
		User::setMusicVol(musicSlider.value() * 20);
	});
  connect(&keys, &QPushButton::pressed, [this]() {
    SFX::SELECT1.play(25);
		switch (User::getControls()) {
			case 0:
				keys.setText(Controls::WASD);
				User::setControls(Controls::WASD);
				break;
			case 1:
				keys.setText(Controls::IJKL);
				User::setControls(Controls::IJKL);
				break;
			case 2:
				keys.setText(Controls::TRAD);
				User::setControls(Controls::TRAD);
		}
  });
  connect(&backOptions, &QPushButton::clicked, [this]() {
    optionsMenu.hide();
    mainMenu.show();
    adjustSize();
    SFX::SELECT2.play(25);
  });
  //************************************************************
  serverMenu.setLayout(&serverLayout);
  serverLayout.addWidget(&connectionInfo, 1, 1, 1, -1);
  serverLayout.addWidget(&serverStatus, 2, 1, 1, -1);
  serverLayout.addWidget(&playerCount, 3, 1, 1, -1);
  serverLayout.addWidget(&backServer, 4, 1, 1, -1);
  connect(&backServer, &QPushButton::clicked, [this]() {
    Server::destruct();
    serverMenu.hide();
    multiplayerMenu.show();
    adjustSize();
    SFX::SELECT2.play(25);
    Music::MENU.play();
  });
  //************************************************************
  lobbyMenu.setLayout(&lobbyLayout);
  lobbyLayout.addWidget(&players, 1, 1, 1, -1);
  lobbyLayout.addWidget(&playerLobby, 2, 1, 1, -1);
	lobbyLayout.addWidget(&readyLobby, 3, 1, 1, -1);
  lobbyLayout.addWidget(&backLobby, 4, 1, 1, -1);
  connect(&playerLobby, &QPushButton::clicked, [this]() {
		SFX::SELECT1.play(25);
		switch (Character::valueOf(User::getCharacter())) {
			case 0:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
				break;
			case 1:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
				break;
			case 2:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
				break;
			case 3:
				User::setCharacter(Character::PYACHI);
				playerSingle.setText(Character::PYACHI);
				playerLobby.setText(Character::PYACHI);
				break;
		}
  });
	connect(&readyLobby, &QPushButton::clicked, [this]() {
		if (readyLobby.text().contains("☐")) {
			Connection::sendPacket(S_READY);
			readyLobby.setText("Ready Up ☑");
		} else {
			Connection::sendPacket(S_UNREADY);
			readyLobby.setText("Ready Up ☐");
		}
	});
  connect(&backLobby, &QPushButton::clicked, [this]() {
    Connection::destruct();
    lobbyMenu.hide();
    multiplayerMenu.show();
    adjustSize();
    SFX::DISCONNECT.play();
  });
}
