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

  Scoreboard* score = new Scoreboard("hello");
  score->Add_Score(
      "hello", "brad",
      QDateTime::fromString("2021-10-04 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      2000);
  score->Add_Score(
      "hello", "brad",
      QDateTime::fromString("2021-10-05 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      2500);
  score->Add_Score(
      "hello", "brad",
      QDateTime::fromString("2021-10-06 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      2250);
  score->Add_Score(
      "hello", "brad",
      QDateTime::fromString("2021-10-07 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      1500);
  score->Add_Score(
      "hello", "brad",
      QDateTime::fromString("2021-10-08 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      3000);

  score->Add_Score(
      "hello", "brad",
      QDateTime::fromString("2021-10-09 10:43:12", "yyyy-MM-dd HH:mm:ss"),
      1700);

  //    score->Show_Scoreboard();

  database_API dataAPI;
  dataAPI.start_connection("SQLITE");

  QSqlDatabase dab = dataAPI.start_connection("SQLITE");
  QSqlQuery query = QSqlQuery(dab);
  qDebug() << "--Create level table: ";
  qDebug() << dataAPI.create_level_table(score->Get_Level());
  qDebug() << "--Update database: ";
  qDebug() << dataAPI.update_database(score->Get_Level(), score);
  Scoreboard* holder = dataAPI.get_scoreboard("hello");
  qDebug() << "--Returned Table: ";
  holder->Show_Scoreboard();

  qDebug() << "Create settings table :";
	qDebug() << dataAPI.create_settings_table(soundVol, musicVol, *controls,
																						*character);

  soundVol = dataAPI.get_SFX();
  musicVol = dataAPI.get_music();
	controls = &Controls::valueOf(dataAPI.get_controls());
	character = &Character::valueOf(dataAPI.getCharacter());

  //        for( int i = 0; i < lenLevels; i++)
  //        {
  //            masterBoard[i] = dataAPI.get_scoreboard(ScoreLevels[i]);
  //        }

  dataAPI.close_database();

	atexit([]() {
		database_API dataAPI;
		dataAPI.start_connection("SQLITE");
		dataAPI.update_settings(User::getSoundVol(), User::getMusicVol(),
														User::getControls(), User::getCharacter());
		dataAPI.close_database();
	});
}
