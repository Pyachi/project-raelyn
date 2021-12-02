#include "database.h"
#include <QDir>
#include <QSqlQuery>
#include "scoreboard.h"
#include "user.h"

Database* Database::DB = nullptr;

Database& Database::create(const String& user) {
	if (DB == nullptr) {
		DB = new Database(QString::fromStdString(user));
		DB->db.setDatabaseName(QDir::currentPath() + "/data");
		DB->db.open();
	}
	return *DB;
}

Database& Database::get() {
	if (DB == nullptr) {
		DB = new Database(QString::fromStdString(User::getName()));
		DB->db.setDatabaseName(QDir::currentPath() + "/data");
		DB->db.open();
	}
	return *DB;
}

// addes a new entry into the database
bool Database::add(const Entry& entry) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "INSERT INTO scores (User, Time, Score) VALUES ('";
	querySTR.append(entry.user);
	querySTR.append("', '");
	querySTR.append(entry.time.toString("yyyyMMdd HH:mm:ss"));
	querySTR.append("', ");
	querySTR.append(QString::number(entry.score));
	querySTR.append(");");
	return query.exec(querySTR);
}

// returns the entire scoreboard stored in the database
Scoreboard Database::getMasterboard() {
	Scoreboard board;

	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM scores;";

	query.exec(querySTR);

	while (query.next()) {
		QDateTime tim =
				QDateTime::fromString(query.value(1).toString(), "yyyyMMdd HH:mm:ss");
		board.add({query.value(0).toString(), query.value(2).toLongLong(), tim});
	}

	return board;
}

// returns a scoreboard that contains all the entries
// from the given user
Scoreboard Database::getPlayerboard(QString use) {
	Scoreboard board;

	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM scores WHERE User = '";
	querySTR.append(use);
	querySTR.append("';");

	query.exec(querySTR);

	while (query.next()) {
		QDateTime tim =
				QDateTime::fromString(query.value(1).toString(), "yyyyMMdd HH:mm:ss");

		board.add({query.value(0).toString(), query.value(2).toLongLong(), tim});
	}

	return board;
}

// create a new table to store the entries in
void Database::createScoreTable() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR =
			"CREATE TABLE IF NOT EXISTS scores (User TEXT, Time DATETIME UNIQUE "
			"PRIMARY KEY, Score long);";

	query.exec(querySTR);
}

// creates a table in the database to hold the settings
void Database::createSettingsTable(int SFX,
																	 int music,
																	 int controls,
																	 int character) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR =
			"CREATE TABLE IF NOT EXISTS settings (User TEXT UNIQUE PRIMARY KEY, SFX "
			"INT, Music INT, Controls INT, Character INT, IP TEXT, Port SMALLINT);";

	query.exec(querySTR);

	querySTR = "INSERT INTO settings VALUES ('";
	querySTR.append(user);
	querySTR.append("', ");
	querySTR.append(QString::number(SFX));
	querySTR.append(", ");
	querySTR.append(QString::number(music));
	querySTR.append(", ");
	querySTR.append(QString::number(controls));
	querySTR.append(", ");
	querySTR.append(QString::number(character));
	querySTR.append(", '127.0.0.1', 1337);");

	query.exec(querySTR);
}

// updates the user's settings with the current settings
void Database::updateSettings(int SFX, int music, int controls, int character) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "UPDATE settings SET SFX = ";
	querySTR.append(QString::number(SFX));
	querySTR.append(", Music = ");
	querySTR.append(QString::number(music));
	querySTR.append(", Controls = ");
	querySTR.append(QString::number(controls));
	querySTR.append(", Character = ");
	querySTR.append(QString::number(character));
	querySTR.append(" WHERE User = '");
	querySTR.append(user);
	querySTR.append("';");

	query.exec(querySTR);
}

// returns the SFX volume from database
int Database::getSFXVol() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	query.exec(querySTR);
	query.next();
	return query.value(1).toInt();
}

// returns the Music volume from database
int Database::getMusicVol() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	query.exec(querySTR);
	query.next();
	return query.value(2).toInt();
}

// returns the controls from the database
int Database::getControls() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	query.exec(querySTR);
	query.next();
	return query.value(3).toInt();
}

// returns the character from the database
int Database::getCharacter(void) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	query.exec(querySTR);
	query.next();
	return query.value(4).toInt();
}

// updates the network settings in the database, given
// the passed settings
void Database::updateNetwork(QString ip, unsigned short port) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "UPDATE settings SET IP = '";
	querySTR.append(ip);
	querySTR.append("', Port = ");
	querySTR.append(QString::number(port));
	querySTR.append(";");
	query.exec(querySTR);
}

// returns the IP address from the database
const QString Database::getIP() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	query.exec(querySTR);
	query.next();
	return query.value(5).toString();
}

// returns the port from the database
const QString Database::getPort() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	query.exec(querySTR);
	query.next();
	return query.value(6).toString();
}
