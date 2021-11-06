#include <QApplication>
#include "menu/mainmenu.h"
#include "database/scoreboard.cpp"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	srand(time(0));

	MainMenu::openMenu();

    Scoreboard *score = new Scoreboard();
    score->Add_Score("hello", "brad", 2000);
    score->Add_Score("hello", "brad", 2500);
    score->Add_Score("hello", "brad", 2250);
    score->Add_Score("hello", "brad", 1500);
    score->Add_Score("hello", "brad", 3000);

    score->Show_Scoreboard();

	return a.exec();
}
