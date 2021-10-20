#include <QApplication>
#include "menu/mainmenu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	MainMenu* menu = new MainMenu;
	menu->show();

	return a.exec();
}
