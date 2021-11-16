#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include "uid.h"

User* User::USER = nullptr;

User::User()
    : name(QDir::homePath().split('/').last().toStdString()),
      character(Character::PYACHI.name),
      controls({Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right,
                Qt::Key_Shift, Qt::Key_Z, Qt::Key_X}),
      soundVol(100),
      musicVol(100) {
  for (const QHostAddress& address : QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol &&
        address.isLoopback() == false) {
      ip = address.toString().toStdString();
      break;
    }
  }
}
