#include "database_api.h"

database_API::database_API() {}

database_API::database_API(QString type, QString use)
{
    start_connection(type, use);
}

QSqlDatabase database_API::start_connection(QString type, QString use) {
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

QSqlDatabase database_API::start_connection(QString type,
																						QString use,
																						QString host,
																						int port,
																						QString name,
																						QString SQLuser,
																						QString pass) {
	QSqlDatabase start = QSqlDatabase::addDatabase(
			type);  // starts the type of SQL database to be used (SQLite, MySQL)
	if (type == "MYSQL") {
		start.setHostName(host);  // adds connection details to session
		start.setPort(port);
		start.setDatabaseName(name);
		start.setUserName(SQLuser);
		start.setPassword(pass);

		if (!start.open())  // opens connection
		{
			//			qDebug() << "Error: Unable to connect to above
			//error.";
		}
	}
	db = start;

	user = use;
	return start;
}

bool database_API::add_score(QString user, QDateTime time, int score) {
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
		//time.toString();
		pass = false;
	}

	return pass;
}

Scoreboard* database_API::get_scoreboard() {

	Scoreboard* board = new Scoreboard();

	QSqlQuery query = QSqlQuery(db);
	QString querySTR = "SELECT * FROM scores;";

	if (!query.exec(querySTR)) {
		//        qDebug() << "Error: invalid query get scoreboard";
	}



	while (query.next()) {
        QDateTime tim =
                QDateTime::fromString(query.value(1).toString(), "yyyyMMdd HH:mm:ss");
        board->Add_Score(query.value(0).toString(), tim, query.value(2).toInt());
	}

	return board;
}

Scoreboard* database_API::get_scoreboard(QString use) {

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

		board->Add_Score(query.value(0).toString(), tim, query.value(2).toInt());
	}

	return board;
}

bool database_API::update_database(Scoreboard* score) {
	bool pass = true;
	Scoreboard* data = get_scoreboard();
	Scoreboard* diff;

	if (data == nullptr) {
        qDebug() << "data = null";
		diff = score;
    }
    else {
		diff = score->Extra_Here(data);
	}

	for (int i = 0; i < diff->Get_length(); i++) {
		Scoreboard::run* hold = diff->Get_Run(i);
		pass = pass && add_score(hold->user, hold->time, hold->score);
	}
	return pass;
}

bool database_API::create_level_table() {

	bool pass = true;

	QSqlQuery query = QSqlQuery(db);
	QString querySTR =
			"CREATE TABLE IF NOT EXISTS scores (User TEXT, Time DATETIME UNIQUE "
			"PRIMARY KEY, Score int);";

	if (!query.exec(querySTR)) {
		//		qDebug() << "Error: invalid query for create_level_table";
		pass = false;
	}

	return pass;
}

bool database_API::create_settings_table(int SFX,
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

void database_API::update_settings(int SFX,
																	 int music,
																	 int controls,
																	 int character) {
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

int database_API::get_SFX() {
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

int database_API::get_music() {
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

int database_API::get_controls() {
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

int database_API::getCharacter(void) {
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

void database_API::update_network(QString ip, unsigned short port)
{
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

const QString database_API::get_IP()
{
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

const QString database_API::get_port()
{
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
void database_API::close_database() { db.close(); }
