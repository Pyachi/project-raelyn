#include "database_api.h"

database_API::database_API()
{

}

QSqlDatabase database_API::start_connection(QString type, QString host, int port, QString name, QString user, QString pass)
{


    QSqlDatabase start = QSqlDatabase::addDatabase(type);       // starts the type of SQL database to be used (SQLite, MySQL)
    if(type == "MYSQL")
    {
        start.setHostName(host);                                    // adds connection details to session
        start.setPort(port);
        start.setDatabaseName(name);
        start.setUserName(user);
        start.setPassword(pass);

        if(!start.open())                                           // opens connection
        {
            qDebug() << start.lastError();
            qDebug() << "Error: Unable to connect to above error.";
        }
    }
    db = start;

    return start;
}

QSqlDatabase database_API::start_connection(QString type)
{
    // should be used only for SQLITE databases

    db = QSqlDatabase::addDatabase("QSQLITE", type);
    if(type == "SQLITE")
    {
        db.setDatabaseName(QDir::currentPath() + "/scores");         // creates the name and path where
    }                                                                   // the database should be stored

    if(!db.open())                               // tries to open/create the database file
    {
        qDebug() << db.lastError().text();       // if fail display error
    }
    else {
        qDebug() << "Database opened at: " + QDir::currentPath() + "/scores";   // if successful display where it opened
    }

    return db;       // returns database object
}

bool database_API::add_score(QString level, QString user, QDateTime time, int score)
{
    bool pass = true;
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "INSERT INTO " + level + " (Time, User, Level, Score) VALUES ('";


    querySTR.append(time.toString("yyyyMMdd HH:mm:ss"));
    querySTR.append("', '");
    querySTR.append(user);
    querySTR.append("', '");
    querySTR.append(level);
    querySTR.append("', ");
    querySTR.append(QString::number(score));
    querySTR.append(");");

    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query from adding score" + time.toString();
        pass = false;
    }


    return pass;

}

Scoreboard* database_API::get_scoreboard(QString level)
{
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "SELECT * FROM ";
    querySTR.append(level);

    Scoreboard* board = new Scoreboard(level);

    querySTR.append(";");
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query get scoreboard " + level;
    }

    while(query.next())
    {
        board->Add_Score(query.value(1).toString(), query.value(2).toString(), query.value(0).toDateTime(), query.value(3).toInt());
    }

    return board;
}

bool database_API::update_database(QString name, Scoreboard* score)
{
    bool pass = true;
    Scoreboard* data = get_scoreboard(name);
    Scoreboard* diff;
    if(data == nullptr)
    {
        diff = score;
    }
    else
    {
        diff = score->Extra_Here(data);
        qDebug() << "get diff";
    }

    for(int i = 0; i < diff->Get_length(); i++)
    {
        Scoreboard::run* hold = diff->Get_Run(i);
        pass = pass && add_score(hold->level, hold->user, hold->time, hold->score);
    }
    return pass;
}



bool database_API::create_level_table(QString level)
{  
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "CREATE TABLE IF NOT EXISTS ";
    bool pass = true;

    querySTR.append(level);
    querySTR.append(" (Time DATETIME UNIQUE PRIMARY KEY, User TEXT, Level TEXT, Score int);");
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query for create_level_table";
        pass = false;
    }

    return pass;
}

bool database_API::create_settings_table(int SFX, int music, Array<int> controls)
{
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "CREATE TABLE IF NOT EXISTS settings (ID INT UNIQUE PRIMARY KEY, SFX INT, Music INT);";
    bool pass = true;

    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query for create_settings_table 1";
        pass = false;
    }

    querySTR = "CREATE TABLE IF NOT EXISTS controls (ID INT UNIQUE PRIMARY KEY, up INT, left INT, down INT, right INT, focus INT, shoot INT, bomb INT);";
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query for create_settings_table 2";
        pass = false;
    }


    querySTR = "INSERT INTO settings VALUES (1, ";
    querySTR.append(QString::number(SFX));
    querySTR.append(", ");
    querySTR.append(QString::number(music));
    querySTR.append(");");

    qDebug() << querySTR;

    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query for create_settings_table 3";
        pass = false;
    }

    querySTR = "INSERT INTO controls VALUES (1, ";
    querySTR.append(QString::number(controls[0]));
    querySTR.append(", ");
    querySTR.append(QString::number(controls[1]));
    querySTR.append(", ");
    querySTR.append(QString::number(controls[2]));
    querySTR.append(", ");
    querySTR.append(QString::number(controls[3]));
    querySTR.append(", ");
    querySTR.append(QString::number(controls[4]));
    querySTR.append(", ");
    querySTR.append(QString::number(controls[5]));
    querySTR.append(", ");
    querySTR.append(QString::number(controls[6]));
    querySTR.append(");");

    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query for create_settings_table 4";
        pass = false;
    }

    return pass;
}

void database_API::update_settings(int SFX, int music, Array<int> controls)
{
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "UPDATE settings SET SFX = ";
    querySTR.append(QString::number(SFX));
    querySTR.append(", Music = ");
    querySTR.append(QString::number(music));
    querySTR.append(";");

    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query update settings";
    }

    querySTR = "UPDATE controls SET up = ";
    querySTR.append(QString::number(controls[0]));
    querySTR.append(", left = ");
    querySTR.append(QString::number(controls[1]));
    querySTR.append(", down = ");
    querySTR.append(QString::number(controls[2]));
    querySTR.append(", right = ");
    querySTR.append(QString::number(controls[3]));
    querySTR.append(", focus = ");
    querySTR.append(QString::number(controls[4]));
    querySTR.append(", shoot = ");
    querySTR.append(QString::number(controls[5]));
    querySTR.append(", bomb = ");
    querySTR.append(QString::number(controls[6]));
    querySTR.append(";");

    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query update controls";
    }

}


int database_API::get_SFX()
{
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "SELECT * FROM settings;";
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query get SFX";
    }
    query.next();
    return query.value(1).toInt();
}

int database_API::get_music()
{
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "SELECT * FROM settings;";
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query get settings 1";
    }
    query.next();
    return query.value(2).toInt();
}


Array<int> database_API::get_controls(Array<int> controls)
{
    QSqlQuery query = QSqlQuery(db);
    QString querySTR = "SELECT * FROM controls";
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query get settings 2";
    }

    query.next();

    controls[0] = query.value(1).toInt();
    controls[1] = query.value(2).toInt();
    controls[2] = query.value(3).toInt();
    controls[3] = query.value(4).toInt();
    controls[4] = query.value(5).toInt();
    controls[5] = query.value(6).toInt();
    controls[6] = query.value(7).toInt();

    return controls;
}


void database_API::close_database()
{
    db.close();
}
