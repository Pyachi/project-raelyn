#ifndef SINGLEPLAYERMENU_H
#define SINGLEPLAYERMENU_H

#include <QDialog>

class SingleplayerMenu : public QDialog {
 public:
	SingleplayerMenu();

 private:
	void changeCharacter();
	void changeDifficulty();
	void startGame();
	void returnToMenu();
};

#endif  // SINGLEPLAYERMENU_H
