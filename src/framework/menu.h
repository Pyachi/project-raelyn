#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include "character.h"
#include "music.h"
#include "database.h"
#include "user.h"

class Menu : public QDialog {
 public:
	Database* dataAPI =
			new Database("SQLITE", QString::fromStdString(User::getName()));
	const QString database_ip = dataAPI->getIP();
	const QString database_port = dataAPI->getPort();
	static void openMenu(void) {
		if (MENU == nullptr)
			MENU = new Menu();
		MENU->show();
		Music::MENU.play();
	}

 private:
	Menu(void);

	static Menu* MENU;
	//***************************************************************************
	// Widgets
	QWidget mainMenu;
	QWidget singleplayerMenu;
	QWidget multiplayerMenu;
	QWidget optionsMenu;
	QWidget lobbyMenu;
	QWidget serverMenu;
	//***************************************************************************
	// Layouts
	QGridLayout layout;
	QGridLayout mainLayout;
	QGridLayout singleplayerLayout;
	QGridLayout multiplayerLayout;
	QGridLayout optionsLayout;
	QGridLayout serverLayout;
	QGridLayout lobbyLayout;
	//***************************************************************************
	// Main
	QLabel title;
	QPushButton singleplayer;
	QPushButton multiplayer;
	QPushButton options;
	QPushButton quit;
	//***************************************************************************
	// Singleplayer
	QPushButton playerSingle;
	QPushButton start;
	QPushButton backSingleplayer;
	//***************************************************************************
	// Multiplayer
	QLineEdit ipForm;
	QRegExpValidator ipValidator;
	QLineEdit portForm;
	QRegExpValidator portValidator;
	QPushButton host;
	QPushButton join;
	QPushButton backMultiplayer;
	QString lastIP;
	unsigned short lastPort;
	//***************************************************************************
	// Options
	QLabel soundLabel;
	QSlider soundSlider;
	QLabel musicLabel;
	QSlider musicSlider;
	QPushButton keys;
	QPushButton backOptions;
	//***************************************************************************
	// Server
	QLabel connectionInfo;
	QLabel serverStatus;
	QLabel playerCount;
	QPushButton backServer;
	//***************************************************************************
	// Lobby
	QListWidget players;
	QPushButton playerLobby;
	QPushButton readyLobby;
	QPushButton backLobby;
	//***************************************************************************
	friend class Connection;
	friend class Server;
};

#endif  // MAINMENU_H
