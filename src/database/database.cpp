#include "database.h"

Database::Database() {}

Database::Database(QString type, QString use) { connect(type, use); }

QSqlDatabase Database::connect(QString type, QString use) {
	// should be used only for SQLITE databases

	db = QSqlDatabase::addDatabase("QSQLITE");
	if (type == "SQLITE") {
		db.setDatabaseName(QDir::currentPath() +
											 "/data");  // creates the name and path where
	}                               // the database should be stored

	if (!db.open())  // tries to open/create the database file
	{
		//        qDebug() << db.lastError().text();  // if fail display error
	} else {
		//        qDebug() << "Database opened at: " + QDir::currentPath() +
		//                                        "/scores";  // if successful
		// display where it opened
	}
	user = use;
	return db;  // returns database object
}

bool Database::add(QString user, QDateTime time, long score) {
	bool pass = true;
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "INSERT INTO scores (User, Time, Score) VALUES ('";
	querySTR.append(user);
	querySTR.append("', '");
	querySTR.append(time.toString("yyyyMMdd HH:mm:ss"));
	querySTR.append("', ");
	querySTR.append(QString::number(score));
	querySTR.append(");");

	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query from adding score" +
		// time.toString();
		pass = false;
	}

	return pass;
}

Scoreboard* Database::getScoreboard() {

	Scoreboard* board = new Scoreboard();

	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM scores;";

	if (!query.exec(querySTR)) {
		//        qDebug() << "Error: invalid query get scoreboard";
	}

	while (query.next()) {
		QDateTime tim =
				QDateTime::fromString(query.value(1).toString(), "yyyyMMdd HH:mm:ss");
		board->add(query.value(0).toString(), tim, query.value(2).toLongLong());
	}

	return board;
}

Scoreboard* Database::getScoreboard(QString use) {

	Scoreboard* board = new Scoreboard();

	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM scores WHERE User = '";
	querySTR.append(use);
	querySTR.append("';");

	if (!query.exec(querySTR)) {
		//        qDebug() << "Error: invalid query get scoreboard";
	}

	while (query.next()) {
		QDateTime tim =
				QDateTime::fromString(query.value(1).toString(), "yyyyMMdd HH:mm:ss");

		board->add(query.value(0).toString(), tim, query.value(2).toLongLong());
	}

	return board;
}

bool Database::update(Scoreboard* score) {
	bool pass = true;
	Scoreboard* data = getScoreboard();
	Scoreboard* diff;

	if (data == nullptr) {
		qDebug() << "data = null";
		diff = score;
	} else {
		diff = score->extraHere(data);
	}

	for (int i = 0; i < diff->getLength(); i++) {
		Scoreboard::Entry* hold = diff->get(i);
		pass = pass && add(hold->user, hold->time, hold->score);
	}
	return pass;
}

bool Database::createLevelTable() {

	bool pass = true;

	QSqlQuery query = QSqlQuery(db);
	QString querySTR =
			"CREATE TABLE IF NOT EXISTS scores (User TEXT, Time DATETIME UNIQUE "
			"PRIMARY KEY, Score long);";

	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query for create_level_table";
		pass = false;
	}

	return pass;
}

bool Database::createSettingsTable(int SFX,
																	 int music,
																	 int controls,
																	 int character) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR =
			"CREATE TABLE IF NOT EXISTS settings (User TEXT UNIQUE PRIMARY KEY, SFX "
			"INT, Music INT, Controls INT, Character INT, IP TEXT, Port SMALLINT);";
	bool pass = true;

	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query for create_settings_table 1";
		pass = false;
	}

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
	//    qDebug() << querySTR;
	if (!query.exec(querySTR)) {
		//        qDebug() << "Error: invalid query for create_settings_table first
		// incert";
		pass = false;
	}

	return pass;
}

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

	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query update settings";
	}
}

int Database::getSFXVol() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query get SFX";
	}
	query.next();
	return query.value(1).toInt();
}

int Database::getMusicVol() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query get settings 1";
	}
	query.next();
	return query.value(2).toInt();
}

int Database::getControls() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query get settings 2";
	}
	query.next();
	return query.value(3).toInt();
}

int Database::getCharacter(void) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query get settings 2";
	}
	query.next();
	return query.value(4).toInt();
}

void Database::updateNetwork(QString ip, unsigned short port) {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "UPDATE settings SET IP = '";
	querySTR.append(ip);
	querySTR.append("', Port = ");
	querySTR.append(QString::number(port));
	querySTR.append(";");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query update network";
	}
}

const QString Database::getIP() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query get settings 2";
	}
	query.next();
	return query.value(5).toString();
}

const QString Database::getPort() {
	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM settings WHERE User = '";
	querySTR.append(user);
	querySTR.append("';");
	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query get settings 2";
	}
	query.next();
	return query.value(6).toString();
}
void Database::close() { db.close(); }
