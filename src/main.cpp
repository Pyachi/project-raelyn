#include <QApplication>
#include "menu.h"
#include "texture.h"
#include "user.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  User::create();

  Menu::openMenu();

	a.setWindowIcon(QIcon(Texture::ICON));

  return a.exec();
}
