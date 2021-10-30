#include "multiplayermenu.h"
#include <QGridLayout>
#include <QRegExpValidator>
#include "mainmenu.h"

MultiplayerMenu* MultiplayerMenu::MENU = nullptr;

MultiplayerMenu::MultiplayerMenu()
		: QDialog(),
			portDisplay("Port:"),
			portForm("7"),
			connectButton("Connect"),
			quitButton("Back") {
	QGridLayout* layout = new QGridLayout;
	setLayout(layout);
	setFixedSize(200, 120);

	layout->addWidget(&portDisplay, 1, 1, 1, 1);

	portForm.setValidator(new QRegExpValidator(
			QRegExp("^(0|[1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}"
							"|655[0-2][0-9]|6553[0-5])$")));
	layout->addWidget(&portForm, 1, 2, 1, 1);

	layout->addWidget(&connectButton, 2, 1, 1, -1);
	connect(&connectButton, &QPushButton::clicked, this, &MultiplayerMenu::join);

	layout->addWidget(&quitButton, 3, 1, 1, -1);
	connect(&quitButton, &QPushButton::clicked, this,
					&MultiplayerMenu::returnToMenu);
}

void MultiplayerMenu::openMenu() {
	if (MENU == nullptr)
		MENU = new MultiplayerMenu();
	MENU->show();
}

void MultiplayerMenu::join() {}

void MultiplayerMenu::returnToMenu() {
	MainMenu::openMenu();
	close();
}
