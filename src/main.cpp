#include <QApplication>
#include "menu/mainmenu.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(quint32(time(nullptr)));

	//QDir::home().path().split('/').last()

	MainMenu::openMenu();

	return a.exec();
}
