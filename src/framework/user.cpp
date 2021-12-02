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

    Database dataAPI(QString::fromStdString(name));         // starts connection to database
    QSqlQuery query = QSqlQuery(dataAPI.getDatabase());
    dataAPI.createLevelTable();                             // if no scores table, make one

    masterBoard = dataAPI.getScoreboard();                                  // gets the scoreboards from the database
	playerBoard = dataAPI.getScoreboard(QString::fromStdString(name));

    masterBoard->sort();            // sort the boards in decending score order
	playerBoard->sort();

    dataAPI.createSettingsTable(soundVol, musicVol, *controls, *character); // if no settings table, make one

    soundVol = dataAPI.getSFXVol();         // set settings to ones in database
	musicVol = dataAPI.getMusicVol();
	controls = &Controls::valueOf(dataAPI.getControls());
    character = &Character::valueOf(dataAPI.getCharacter());
    dataAPI.close();

  atexit([]() {
        Database dataAPI(QString::fromStdString(User::getName()));
//		dataAPI.connect("SQLITE", QString::fromStdString(User::getName()));
		dataAPI.updateSettings(User::getSoundVol(),
													 User::getMusicVol(),
													 User::getControls(),
													 User::getCharacter());
		dataAPI.close();
  });
}
