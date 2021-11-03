#include "lobbymenu.h"
#include <QGridLayout>

LobbyMenu* LobbyMenu::MENU = nullptr;

LobbyMenu::LobbyMenu() : QDialog(), text("You are in a lobby :)") {
	QGridLayout* layout = new QGridLayout;
	setLayout(layout);
	setFixedSize(200, 120);
	layout->addWidget(&text, 1, 1, 1, 1);
}

void LobbyMenu::openMenu() {
	if (MENU == nullptr)
		MENU = new LobbyMenu;
	MENU->show();
}
