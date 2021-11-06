#include <QApplication>
#include "game/game.h"
#include "menu/menu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(quint32(time(nullptr)));

	Menu::openMenu();

	return a.exec();
}
