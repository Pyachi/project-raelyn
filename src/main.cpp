#include <QApplication>
#include "menu.h"
#include "sfx.h"
#include "user.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  User::create();

  Menu::openMenu();

  return a.exec();
}
