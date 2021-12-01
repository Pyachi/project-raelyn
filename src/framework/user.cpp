#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include "database.h"
#include "uid.h"

User* User::USER = nullptr;

User::User()
    : name(QDir::homePath().split('/').last().toStdString()),
      character(&Character::PYACHI),
      controls(&Controls::TRAD),
      soundVol(100),
      musicVol(100) {
  for (const QHostAddress& address : QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol &&
        address.isLoopback() == false) {
      ip = address.toString().toStdString();
      break;
    }
  }

	Database dataAPI;
	QSqlDatabase dab = dataAPI.connect("SQLITE", QString::fromStdString(name));
  QSqlQuery query = QSqlQuery(dab);
	//  qDebug() << "--Create level table: ";
	qDebug() << dataAPI.createLevelTable();

	masterBoard = dataAPI.getScoreboard();
	playerBoard = dataAPI.getScoreboard(QString::fromStdString(name));

	masterBoard->sort();
	playerBoard->sort();
  qDebug() << "masterBoard--------------------";
	masterBoard->show();
  qDebug() << "playerBoard--------------------";
	playerBoard->show();

	dataAPI.createSettingsTable(soundVol, musicVol, *controls, *character);

  //    qDebug() << "get settings";
	soundVol = dataAPI.getSFXVol();
	musicVol = dataAPI.getMusicVol();
	controls = &Controls::valueOf(dataAPI.getControls());
	character = &Character::valueOf(dataAPI.getCharacter());
	dataAPI.close();

  atexit([]() {
		Database dataAPI;
		dataAPI.connect("SQLITE", QString::fromStdString(User::getName()));
		dataAPI.updateSettings(User::getSoundVol(),
													 User::getMusicVol(),
													 User::getControls(),
													 User::getCharacter());
		dataAPI.close();
  });
}
