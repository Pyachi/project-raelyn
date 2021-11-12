#include <QApplication>
#include "Framework"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	Menu::openMenu();

	return a.exec();
}
