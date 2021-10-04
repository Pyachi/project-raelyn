#include <QApplication>
#include "src/game/game.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Game w;

	w.show();

	return a.exec();
}
