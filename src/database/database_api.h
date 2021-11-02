#ifndef DATABASE_API_H
#define DATABASE_API_H

#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "scoreboard.h"

class database_API
{
public:
    database_API();
    QSqlDatabase start_connection(QString type, QString host, int port, QString name, QString user, QString pass);
    void add_score(QSqlDatabase db, QString level, QString user, int score);
    Scoreboard get_scoreboard(QSqlDatabase db, QString level);
    void close_database(QSqlDatabase db);

private:
    QSqlDatabase db;
};

#endif // DATABASE_API_H
