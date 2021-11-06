#ifndef DATABASE_API_H
#define DATABASE_API_H

#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "scoreboard.h"
#include <QDateTime>

class database_API
{
public:
    database_API();
    QSqlDatabase start_connection(QString type, QString host, int port, QString name, QString user, QString pass);
    bool add_score(QSqlDatabase db, QDateTime time, QString level, QString user, int score);
    Scoreboard get_scoreboard(QString level);

    bool update_database(QString name, Scoreboard score);
    bool create_level_table(QString level);
    void close_database(QSqlDatabase db);

    bool create_master_table(QString level);        // is this needed?
    int run_table_stats(QString level);             // create object to have stats in


private:

    QSqlDatabase db;
};

#endif // DATABASE_API_H
