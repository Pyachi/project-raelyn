#include "database_api.h"

database_API::database_API()
{

}

QSqlDatabase database_API::start_connection(QString type, QString host, int port, QString name, QString user, QString pass)
{
    QSqlDatabase start = QSqlDatabase::addDatabase(type);

    start.setHostName(name);
    start.setPort(port);
    start.setDatabaseName(name);
    start.setUserName(user);
    start.setPassword(pass);

    if(!start.open())
    {
        qDebug() << start.lastError();
        qDebug() << "Error: Unable to connect to above error.";
    }

    return start;
}

bool database_API::add_score(QSqlDatabase db, QString level, QString user, int score)
{
    bool pass = true;

    QSqlQuery query;
    QString querySTR = "INSERT INTO (Id, Level, User, Score) VALUES (";

    // querySTR.append(Id);
    querySTR.append(", ");
    querySTR.append(level);
    querySTR.append(", ");
    querySTR.append(user);
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


Scoreboard database_API::get_scoreboard(QSqlDatabase db, QString level)
{
    QSqlQuery query;
    QString querySTR = "SELECT * FROM ";

    Scoreboard board;

    querySTR.append(level);
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
