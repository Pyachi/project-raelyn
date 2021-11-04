#include "multiplayermenu.h"
#include <QGridLayout>
#include <QRegExpValidator>
#include <QTcpSocket>
#include "lobbymenu.h"
#include "mainmenu.h"
#include "src/network/connection.h"
#include "src/network/server.h"
#include "src/resources.h"

MultiplayerMenu* MultiplayerMenu::MENU = nullptr;

MultiplayerMenu::MultiplayerMenu()
    : QDialog(),
			ipForm("127.0.0.1"),
			portForm("1337"),
      hostButton("Host"),
      joinButton("Join"),
      quitButton("Back") {
  QGridLayout* layout = new QGridLayout;
  setLayout(layout);
  setFixedSize(200, 120);

  ipForm.setValidator(new QRegExpValidator(
      QRegExp("[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}")));
  layout->addWidget(&ipForm, 1, 1, 1, 1);

	portForm.setValidator(new QRegExpValidator(
			QRegExp("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}"
							"|655[0-2][0-9]|6553[0-5])$")));
  layout->addWidget(&portForm, 1, 2, 1, 1);

  layout->addWidget(&hostButton, 2, 1, 1, 1);
  connect(&hostButton, &QPushButton::clicked, this, &MultiplayerMenu::host);

  layout->addWidget(&joinButton, 2, 2, 1, 1);
  connect(&joinButton, &QPushButton::clicked, this, &MultiplayerMenu::join);

  layout->addWidget(&quitButton, 3, 1, 1, -1);
	connect(&quitButton, &QPushButton::clicked, this,
					&MultiplayerMenu::returnToMenu);
}

void MultiplayerMenu::openMenu() {
  if (MENU == nullptr)
    MENU = new MultiplayerMenu();
  MENU->show();
}

void MultiplayerMenu::host() {
	if (!Server::create(portForm.text().toUShort())) {
    Sound::playSound(SFX::SELECT_2, 0.1);
    return;
  }

	Server::viewServer();
  Sound::playSound(SFX::SELECT_1, 0.1);
  close();
}

void MultiplayerMenu::join() {
	if (Connection::create(ipForm.text(), portForm.text().toUShort())) {
		LobbyMenu::openMenu();
		Connection::sendPacket("updateLobbyMenu;");
		close();
	}
}

void MultiplayerMenu::returnToMenu() {
  MainMenu::openMenu();
  Sound::playSound(SFX::SELECT_2, 0.1);
  close();
}

void MultiplayerMenu::closeMenu() {
	if (MENU != nullptr)
		MENU->close();
}
