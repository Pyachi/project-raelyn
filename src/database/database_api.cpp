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
    QSqlQuery q;
    QString query = "SELECT * FROM ";

    Scoreboard board;

    query.append(level);
    if(!q.exec(query))
    {
        qDebug() << db.lastError();
        qDebug() << "Error: invalid query";
    }

    return board;
}

void database_API::close_database(QSqlDatabase db)
{
    db.close();
}
