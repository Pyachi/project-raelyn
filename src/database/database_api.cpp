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

void database_API::add_score(QSqlDatabase db, QString level, QString user, int score)
{
    QSqlQuery q;
    QString query = "ADD ";

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

}



bool database_API::create_level_table(QString level)
{

}

void database_API::close_database(QSqlDatabase db)
{
    db.close();
}
