#ifndef MENU_H
#define MENU_H

#include <QDialog>

class Menu : public QDialog {
 public:
	Menu();

 private:
	void singleplayer();
	void multiplayer();
	void options();
	void quit();
};

#endif  // MENU_H
