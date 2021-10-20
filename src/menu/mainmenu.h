#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

class MainMenu : public QDialog {
 public:
	MainMenu();

 private:
	void openSingleplayerMenu();
	void openMultiplayerMenu();
	void openOptionsMenu();
};

#endif  // MAINMENU_H
