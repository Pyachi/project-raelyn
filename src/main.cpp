#include <QApplication>
#include "framework/menu.h"
#include "database/scoreboard.cpp"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	Menu::openMenu();

	return a.exec();
}
