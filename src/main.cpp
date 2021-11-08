#include "framework/menu.h"
#include <QApplication>
#include <chrono>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(static_cast<unsigned int>(time(nullptr)));

	Menu::openMenu();

	return a.exec();
}
