#include "menu.h"
#include <QApplication>
#include <chrono>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	// Guarantees 100% different srand every time
	srand(static_cast<unsigned int>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch())
					.count()));

	Menu::openMenu();

	return a.exec();
}
