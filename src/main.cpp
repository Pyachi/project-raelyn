#include "src/game/game.h"
#include <QApplication>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(NULL));
    Game w;
    w.show();
    return a.exec();
}
