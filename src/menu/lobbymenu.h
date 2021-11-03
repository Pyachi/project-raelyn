#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include <QDialog>
#include <QLabel>

class LobbyMenu : public QDialog {
 public:
	static void openMenu();

 private:
	LobbyMenu();

	static LobbyMenu* MENU;

	QLabel text;
};

#endif  // LOBBYMENU_H
