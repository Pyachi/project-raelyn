#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include <QSqlQuery>
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

	Database& dataAPI = Database::create(name);  // starts connection to database
	QSqlQuery query = QSqlQuery(dataAPI.getDatabase());
	dataAPI.createScoreTable();  // if no scores table, make one

	masterBoard =
			dataAPI.getMasterboard();  // gets the scoreboards from the database

	dataAPI.createSettingsTable(
			soundVol, musicVol, *controls, *character);  // if no settings table, make
																									 // one

	soundVol = dataAPI.getSFXVol();  // set settings to ones in database
	musicVol = dataAPI.getMusicVol();
	controls = &Controls::valueOf(dataAPI.getControls());
	character = &Character::valueOf(dataAPI.getCharacter());
}

void User::addGame(int score) {
	USER->masterBoard.add({QString::fromStdString(User::getName()), score,
												 QDateTime::currentDateTime()});
}

void User::addExternalScore(int score, const QString& user) {
	USER->masterBoard.add({user, score, QDateTime::currentDateTime()});
}
