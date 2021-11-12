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

    QSqlDatabase start = QSqlDatabase::addDatabase("QSQLITE", type);
    if(type == "SQLITE")
    {
        start.setDatabaseName(QDir::currentPath() + "/scores");         // creates the name and path where
    }                                                                   // the database should be stored

    if(!start.open())                               // tries to open/create the database file
    {
        qDebug() << start.lastError().text();       // if fail display error
    }
    else {
        qDebug() << "Database opened at: " + QDir::currentPath() + "/scores";   // if successful display where it opened
    }
    db = start;         // save the database object into global variable

    return start;       // returns database object
}


void database_API::create_table(QString level)
{

}

bool database_API::add_score(QDateTime time, QString level, QString user, int score)
{
    bool pass = true;
    QSqlQuery query;
    QString querySTR = "INSERT INTO (DATETIME, User, Level, Score) VALUES (";

    querySTR.append(time.toString("yyyy-MM-dd HH:mm:ss"));
    querySTR.append(", ");
    querySTR.append(user);
    querySTR.append(", ");
    querySTR.append(level);
    querySTR.append(", ");
    querySTR.append(score);
    querySTR.append(");");


    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query";
        pass = false;
    }


    return pass;

}

Scoreboard* database_API::get_scoreboard(QString level)
{
    QSqlQuery query;
    QString querySTR = "SELECT * FROM ";
    querySTR.append(level);

    Scoreboard* board = new Scoreboard(level);

    querySTR.append(level);
    querySTR.append(";");
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query";
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

    Scoreboard* diff = score->Extra_Here(data);

    for(int i = 0; i < diff->Get_length(); i++)
    {
        Scoreboard::run* hold = diff->Get_Run(i);
        add_score(hold->time, hold->level, hold->user, hold->score);
    }

    return pass;
}



bool database_API::create_level_table(QString level)
{
    QSqlQuery query;
    QString querySTR = "CREATE TABLE ";
    bool pass = true;

    querySTR.append(level);
    querySTR.append(" (Id: int , Level: TEXT, User: TEXT, Score: int);");
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query";
        pass = false;
    }

    return pass;
}

void database_API::close_database()
{
    db.close();
}
