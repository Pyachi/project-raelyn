#include <QApplication>
#include "menu/mainmenu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(time(0));

	MainMenu::openMenu();

	return a.exec();
}
