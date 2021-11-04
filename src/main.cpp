#include <QApplication>
#include "game/game.h"
#include "menu/mainmenu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(quint32(time(nullptr)));

	MainMenu::openMenu();

	return a.exec();
}
