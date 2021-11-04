#ifndef SINGLEPLAYERMENU_H
#define SINGLEPLAYERMENU_H

#include <QDialog>
#include <QPushButton>

class SingleplayerMenu : public QDialog {
 public:
	static void openMenu();
	static void closeMenu();

 private:
	SingleplayerMenu();

	static SingleplayerMenu* MENU;

	QPushButton characterButton;
	QPushButton difficultyButton;
	QPushButton startButton;
	QPushButton quitButton;

	void changeCharacter();
	void changeDifficulty();
	void startGame();
	void returnToMenu();
};

#endif  // SINGLEPLAYERMENU_H
