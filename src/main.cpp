#include <QApplication>
#include "menu/mainmenu.h"
#include "src/resources.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(time(0));

	Sound::playSound(SFX::EXPL_SUPERHEAVY_2);
	MainMenu::openMenu();

	return a.exec();
}
