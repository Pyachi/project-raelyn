#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include "src/ai/player.h"

class Menu : public QDialog {
 public:
	static void openMenu(void);
	static void closeMenu(void);
	static void updatePlayerCount(int);
	static void updatePlayerList(const QStringList&);

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
	QLabel playerCount;
	QPushButton backServer;

	// Lobby
	QListWidget players;
	QPushButton playerLobby;
	QPushButton startLobby;
	QPushButton backLobby;

	void openSingleplayer(void);
	void openMultiplayer(void);
	void openOptions(void);
	void quitGame(void);
	void startGame(void);
	void returnToMenu(void);
	void hostServer(void);
	void joinServer(void);
	void changeCharacter(void);

	friend class Connection;
};

#endif  // MAINMENU_H
