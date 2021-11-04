#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>

class LobbyMenu : public QDialog {
 public:
	static void openMenu();
	static void closeMenu();

	static void setPlayers(const QStringList&);

 private:
	LobbyMenu();

	static LobbyMenu* MENU;

	QListWidget players;
	QPushButton leaveButton;
	QPushButton startButton;

	void leaveLobby();
	void startGame();
};

#endif  // LOBBYMENU_H
