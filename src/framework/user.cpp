#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include "uid.h"
#include "database_api.h"

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


        database_API dataAPI;
        dataAPI.start_connection("SQLITE");
        qDebug() << "Create settings table :";
        qDebug() << dataAPI.create_settings_table(soundVol, musicVol, controls);

        soundVol = dataAPI.get_SFX();
        qDebug() << soundVol;
        musicVol = dataAPI.get_music();
        qDebug() << musicVol;
        dataAPI.get_controls(controls);


        dataAPI.close_database();
        ip = address.toString().toStdString();
        break;
    }
  }
}
