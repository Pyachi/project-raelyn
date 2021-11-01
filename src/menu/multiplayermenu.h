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

	QLineEdit ipForm;
	QLineEdit portForm;
	QPushButton hostButton;
	QPushButton joinButton;
	QPushButton quitButton;

	void host();
	void join();
	void returnToMenu();
};

#endif  // MULTIPLAYERMENU_H
