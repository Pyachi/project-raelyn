#include "database_api.h"

database_API::database_API()
{

}

QSqlDatabase database_API::start_connection(QString type, QString host, int port, QString name, QString user, QString pass)
{
    QSqlDatabase start = QSqlDatabase::addDatabase(type);       // starts the type of SQL database to be used (SQLite, MySQL)

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

    return start;
}

bool database_API::add_score(QSqlDatabase db, QDateTime time, QString level, QString user, int score)
{
    bool pass = true;

    QSqlQuery query;
    QString querySTR = "INSERT INTO (Time, User, Level, Score) VALUES (";

//    querySTR.append(time);
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


Scoreboard database_API::get_scoreboard(QString level)
{
    QSqlQuery query;
    QString querySTR = "SELECT * FROM ";

    Scoreboard board;

    querySTR.append(level);
    querySTR.append(";");
    if(!query.exec(querySTR))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query";
    }

    while(query.next())
    {
        board.Add_Score(query.value(1).toString(), query.value(2).toString(), query.value(3).toInt());
    }

    return board;
}

bool database_API::update_database(QString name, Scoreboard score)
{
    bool pass = true;
    Scoreboard data = get_scoreboard(name);

    Scoreboard diff = data.Differences(&score);





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

void database_API::close_database(QSqlDatabase db)
{
    db.close();
}
