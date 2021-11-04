#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QPushButton>

class MainMenu : public QDialog {
 public:
	static void openMenu();

 private:
	MainMenu();

	static MainMenu* MENU;

	QPushButton singleplayerButton;
	QPushButton multiplayerButton;
	QPushButton optionsButton;
	QPushButton quitButton;

	void openSingleplayerMenu();
	void openMultiplayerMenu();
	void openOptionsMenu();
};

#endif  // MAINMENU_H
