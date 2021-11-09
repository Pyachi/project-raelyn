#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include "src/ai/playerai.h"

class Menu : public QDialog {
 public:
	static void openMenu();
	static void closeMenu();
	static void updatePlayerCount(int);
	static void updatePlayerList(const QStringList&);

 private:
	Menu();

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
	QPushButton backOptions;

	// Server
	QLabel connectionInfo;
	QLabel playerCount;
	QPushButton backServer;

	// Lobby
	QListWidget players;
	QPushButton playerLobby;
	QPushButton startLobby;
	QPushButton backLobby;

	void openSingleplayer();
	void openMultiplayer();
	void openOptions();
	void quitGame();
	void startGame();
	void returnToMenu();
	void hostServer();
	void joinServer();
	void changeCharacter();

	friend class Connection;
};

#endif  // MAINMENU_H
