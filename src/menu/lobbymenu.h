#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QDialog>
#include <QPushButton>
#include <QListWidget>

class LobbyMenu : public QDialog {
 public:
	static void openMenu();

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
