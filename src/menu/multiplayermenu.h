#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MultiplayerMenu : public QDialog {
 public:
	static void openMenu();

 private:
	MultiplayerMenu();

	static MultiplayerMenu* MENU;

	QLabel portDisplay;
	QLineEdit portForm;
	QPushButton connectButton;
	QPushButton quitButton;

	void join();
	void returnToMenu();
};

#endif  // MULTIPLAYERMENU_H
