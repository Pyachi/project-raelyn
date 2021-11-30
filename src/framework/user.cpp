#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include "database_api.h"
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

  database_API dataAPI;
  QSqlDatabase dab =
      dataAPI.start_connection("SQLITE", QString::fromStdString(name));
  QSqlQuery query = QSqlQuery(dab);
	//  qDebug() << "--Create level table: ";
  qDebug() << dataAPI.create_level_table();

  masterBoard = dataAPI.get_scoreboard();
  playerBoard = dataAPI.get_scoreboard(QString::fromStdString(name));

  masterBoard->Order_Scores("Accending_Score");
  playerBoard->Order_Scores("Accending_Score");
  qDebug() << "masterBoard--------------------";
  masterBoard->Show_Scoreboard();
  qDebug() << "playerBoard--------------------";
  playerBoard->Show_Scoreboard();

  dataAPI.create_settings_table(soundVol, musicVol, *controls, *character);

  //    qDebug() << "get settings";
  soundVol = dataAPI.get_SFX();
  musicVol = dataAPI.get_music();
  controls = &Controls::valueOf(dataAPI.get_controls());
  character = &Character::valueOf(dataAPI.getCharacter());
  dataAPI.close_database();

  atexit([]() {
    database_API dataAPI;
    dataAPI.start_connection("SQLITE", QString::fromStdString(User::getName()));
		dataAPI.update_settings(User::getSoundVol(),
														User::getMusicVol(),
														User::getControls(),
														User::getCharacter());
    dataAPI.close_database();
  });
}
