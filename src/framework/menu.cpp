#include "menu.h"
#include "Network"
#include "Framework"
#include "Assets"

Menu* Menu::MENU = nullptr;

Menu::Menu(void)
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
          "655[0-2][0-9]|6553[0-5])")),
      host("Host"),
      join("Join"),
      backMultiplayer("Return to Menu"),
      soundLabel("Sound Volume:"),
      soundSlider(Qt::Horizontal),
      musicLabel("Music Volume:"),
      musicSlider(Qt::Horizontal),
      keys("Controls: Traditional"),
      backOptions("Return to Menu"),
      serverStatus("Status: In Lobby"),
      playerCount("Players Connected: 0"),
      backServer("Return to Menu"),
      playerLobby("Character: Pyachi"),
      startLobby("Start Game"),
      backLobby("Return to Menu") {
  setLayout(&layout);
  setWindowFlags(Qt::FramelessWindowHint);

  setFixedSize(0, 0);

  title.setPixmap(
      QPixmap(QString::fromStdString(Textures::getTexture(TEXTURE_TITLETEMP))));
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
    SFX::playSound(SFX_SELECT1, 50);
  });
  connect(&multiplayer, &QPushButton::clicked, [this]() {
    mainMenu.hide();
    multiplayerMenu.show();
    adjustSize();
    SFX::playSound(SFX_SELECT1, 50);
  });
  connect(&options, &QPushButton::clicked, [this]() {
    mainMenu.hide();
    optionsMenu.show();
    adjustSize();
    SFX::playSound(SFX_SELECT1, 50);
  });
  connect(&quit, &QPushButton::clicked, [this]() { close(); });
  //************************************************************
  singleplayerMenu.setLayout(&singleplayerLayout);
  singleplayerLayout.addWidget(&playerSingle, 1, 1, 1, -1);
  singleplayerLayout.addWidget(&start, 2, 1, 1, -1);
  singleplayerLayout.addWidget(&backSingleplayer, 3, 1, 1, -1);
  connect(&playerSingle, &QPushButton::clicked, [this]() {
    switch (User::character) {
      case PYACHI:
        User::character = AERON;
        playerSingle.setText("Character: Aeron");
        playerLobby.setText("Character: Aeron");
        SFX::playSound(SFX_SELECT1, 50);
        break;
      case AERON:
        User::character = PRYSMA;
        playerSingle.setText("Character: Prysma");
        playerLobby.setText("Character: Prysma");
        SFX::playSound(SFX_SELECT1, 50);
        break;
      case PRYSMA:
        User::character = ANEKHANDA;
        playerSingle.setText("Character: Anekhanda");
        playerLobby.setText("Character: Anekhanda");
        SFX::playSound(SFX_SELECT1, 50);
        break;
      case ANEKHANDA:
        User::character = PYACHI;
        playerSingle.setText("Character: Pyachi");
        playerLobby.setText("Character: Pyachi");
        SFX::playSound(SFX_SELECT1, 50);
        break;
    }
  });
  connect(&start, &QPushButton::clicked, []() {
    Server::create(0);
    Connection::create("127.0.0.1", Server::getPort());
    Connection::sendPacket(PACKETPLAYINSTARTGAME);
  });
  connect(&backSingleplayer, &QPushButton::clicked, [this]() {
    singleplayerMenu.hide();
    mainMenu.show();
    adjustSize();
    SFX::playSound(SFX_SELECT2, 50);
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
      SFX::playSound(SFX_SELECT2, 50);
      return;
    }
    connectionInfo.setText(User::getIp() + ":" +
                           QString::number(Server::getPort()));
    multiplayerMenu.hide();
    serverMenu.show();
    adjustSize();
    SFX::playSound(SFX_SELECT1, 50);
    Music::stopSong();
  });
  connect(&join, &QPushButton::clicked, [this]() {
    if (Connection::create(ipForm.text(), portForm.text().toUShort())) {
      lobbyMenu.show();
      multiplayerMenu.hide();
      adjustSize();
      Connection::sendPacket(PACKETPLAYINPLAYERJOIN);
    } else
      SFX::playSound(SFX_SELECT2, 50);
  });
  connect(&backMultiplayer, &QPushButton::clicked, [this]() {
    multiplayerMenu.hide();
    mainMenu.show();
    adjustSize();
    SFX::playSound(SFX_SELECT2, 50);
  });
  ipForm.setValidator(&ipValidator);
  portForm.setValidator(&portValidator);
  //************************************************************
  optionsMenu.setLayout(&optionsLayout);
  optionsLayout.addWidget(&soundLabel, 1, 1, 1, -1);
  optionsLayout.addWidget(&soundSlider, 2, 1, 1, -1);
  soundSlider.setMaximum(5);
  soundSlider.setValue(5);
  optionsLayout.addWidget(&musicLabel, 3, 1, 1, -1);
  optionsLayout.addWidget(&musicSlider, 4, 1, 1, -1);
  musicSlider.setMaximum(5);
  musicSlider.setValue(5);
  optionsLayout.addWidget(&keys, 5, 1, 1, -1);
  optionsLayout.addWidget(&backOptions, 6, 1, 1, -1);
  connect(&soundSlider, &QSlider::valueChanged, [this]() {
    SFX::volume = this->soundSlider.value() / 5.0;
    SFX::playSound(SFX_COLLECT2);
  });
  connect(&musicSlider, &QSlider::valueChanged, [this]() {
    Music::changeVolume(this->musicSlider.value() * 20);
  });
  connect(&keys, &QPushButton::pressed, [this]() {
    if (User::getKeyUp() == Qt::Key_Up) {
      keys.setText("Controls: WASD");
      User::keys = {Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D,
                    Qt::Key_L, Qt::Key_K, Qt::Key_J};
      SFX::playSound(SFX_SELECT1, 50);
    } else if (User::getKeyUp() == Qt::Key_W) {
      keys.setText("Controls: IJKL");
      User::keys = {Qt::Key_I, Qt::Key_J, Qt::Key_K, Qt::Key_L,
                    Qt::Key_A, Qt::Key_S, Qt::Key_D};
      SFX::playSound(SFX_SELECT1, 50);
    } else if (User::getKeyUp() == Qt::Key_I) {
      keys.setText("Controls: Traditional");
      User::keys = {Qt::Key_Up,    Qt::Key_Left, Qt::Key_Down, Qt::Key_Right,
                    Qt::Key_Shift, Qt::Key_Z,    Qt::Key_X};
      SFX::playSound(SFX_SELECT1, 50);
    }
  });
  connect(&backOptions, &QPushButton::clicked, [this]() {
    optionsMenu.hide();
    mainMenu.show();
    adjustSize();
    SFX::playSound(SFX_SELECT2, 50);
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
    SFX::playSound(SFX_SELECT2, 50);
    Music::playSong(SONG_MENU);
  });
  //************************************************************
  lobbyMenu.setLayout(&lobbyLayout);
  lobbyLayout.addWidget(&players, 1, 1, 1, -1);
  lobbyLayout.addWidget(&playerLobby, 2, 1, 1, -1);
  lobbyLayout.addWidget(&startLobby, 3, 1, 1, -1);
  lobbyLayout.addWidget(&backLobby, 4, 1, 1, -1);
  connect(&playerLobby, &QPushButton::clicked, [this]() {
    switch (User::character) {
      case PYACHI:
        User::character = AERON;
        playerSingle.setText("Character: Aeron");
        playerLobby.setText("Character: Aeron");
        SFX::playSound(SFX_SELECT1, 50);
        break;
      case AERON:
        User::character = PRYSMA;
        playerSingle.setText("Character: Prysma");
        playerLobby.setText("Character: Prysma");
        SFX::playSound(SFX_SELECT1, 50);
        break;
      case PRYSMA:
        User::character = ANEKHANDA;
        playerSingle.setText("Character: Anekhanda");
        playerLobby.setText("Character: Anekhanda");
        SFX::playSound(SFX_SELECT1, 50);
        break;
      case ANEKHANDA:
        User::character = PYACHI;
        playerSingle.setText("Character: Pyachi");
        playerLobby.setText("Character: Pyachi");
        SFX::playSound(SFX_SELECT1, 50);
        break;
    }
  });
  connect(&startLobby, &QPushButton::clicked, []() {
    Connection::sendPacket(PACKETPLAYINSTARTGAME);
  });
  connect(&backLobby, &QPushButton::clicked, [this]() {
    Connection::destruct();
    lobbyMenu.hide();
    multiplayerMenu.show();
    adjustSize();
    SFX::playSound(SFX_DISCONNECT);
  });
}

void Menu::openMenu(void) {
  if (MENU == nullptr)
    MENU = new Menu();
  MENU->show();
  Music::playSong(SONG_MENU);
}
