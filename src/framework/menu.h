#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include "player.h"

class Menu : public QDialog {
 public:
	static void openMenu(void);

 private:
	Menu(void);

	static Menu* MENU;

	QWidget mainMenu;
	QWidget singleplayerMenu;
	QWidget multiplayerMenu;
	QWidget optionsMenu;
	QWidget lobbyMenu;
	QWidget serverMenu;

	QGridLayout layout;
	QGridLayout mainLayout;
	QGridLayout singleplayerLayout;
	QGridLayout multiplayerLayout;
	QGridLayout optionsLayout;
	QGridLayout serverLayout;
	QGridLayout lobbyLayout;

	QLabel title;

	// Main
	QPushButton singleplayer;
	QPushButton multiplayer;
	QPushButton options;
	QPushButton quit;

	// Singleplayer
	QPushButton playerSingle;
	QPushButton start;
	QPushButton backSingleplayer;

	// Multiplayer
	QLineEdit ipForm;
	QRegExpValidator ipValidator;
	QLineEdit portForm;
	QRegExpValidator portValidator;
	QPushButton host;
	QPushButton join;
	QPushButton backMultiplayer;

	// Options
	QLabel soundLabel;
	QSlider soundSlider;
	QLabel musicLabel;
	QSlider musicSlider;
	QPushButton keys;
	QPushButton backOptions;

	// Server
	QLabel connectionInfo;
	QLabel serverStatus;
	QLabel playerCount;
	QPushButton backServer;

	// Lobby
	QListWidget players;
	QPushButton playerLobby;
	QPushButton startLobby;
	QPushButton backLobby;

	friend class Connection;
	friend class Server;
};

#endif  // MAINMENU_H
