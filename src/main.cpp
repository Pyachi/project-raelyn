#include <AL/al.h>
#include <QApplication>
#include "framework/menu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	Menu::openMenu();

	return a.exec();
}
