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

  Scoreboard* score = new Scoreboard();
  score->Add_Score(
      "bmy0004",
      QDateTime::fromString("2021-10-04 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      2000);
  score->Add_Score(
      "bmy0004",
      QDateTime::fromString("2021-10-05 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      2500);
  score->Add_Score(
      "bmy0004",
      QDateTime::fromString("2021-10-06 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      2250);

  score->Add_Score("GB0001", QDateTime::fromString("2021-11-18 01:01:00", "yyyy-MM-dd HH:mm:ss"),10000000);

  score->Add_Score(
      "bmy0004",
      QDateTime::fromString("2021-10-09 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      1700);

  score->Add_Score(
      "sg0001",
      QDateTime::fromString("2022-10-08 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      9000);

  //    score->Show_Scoreboard();

  database_API dataAPI;
  QSqlDatabase dab =
      dataAPI.start_connection("SQLITE", QString::fromStdString(name));
  QSqlQuery query = QSqlQuery(dab);
	//  qDebug() << "--Create level table: ";
  qDebug() << dataAPI.create_level_table();
	//  qDebug() << "--Update database: ";
  qDebug() << dataAPI.update_database(score);

  Scoreboard* masterBoard = dataAPI.get_scoreboard();
  Scoreboard* playerBoard = dataAPI.get_scoreboard(QString::fromStdString(name));


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
