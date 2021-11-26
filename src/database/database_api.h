#ifndef DATABASE_API_H
#define DATABASE_API_H

#include <qdebug.h>
#include <QDateTime>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "scoreboard.h"
#include "util.h"

class database_API {
 public:
    database_API();
    database_API(QString type, QString use);
    QSqlDatabase start_connection(QString type, QString use);
    QSqlDatabase start_connection(QString type, QString use,
																QString host,
																int port,
																QString name,
                                                                QString SQLuser,
																QString pass);


    bool add_score(QString user, QDateTime time, int score);

    Scoreboard* get_scoreboard();
    Scoreboard* get_scoreboard(QString use);

    bool update_database(Scoreboard* score);
    bool create_level_table();
	bool create_settings_table(int SFX, int music, int controls, int character);
	void update_settings(int SFX, int music, int controls, int character);
	int get_SFX();
	int get_music();
	int get_controls();
	int getCharacter(void);
	void close_database();

    void update_network(QString ip, unsigned short port);
    const QString get_IP();
    const QString get_port();

	bool create_master_table(QString level);  // is this needed?
	int run_table_stats(QString level);       // create object to have stats in

 private:
    QString user;
	QSqlDatabase db;
};

#endif  // DATABASE_API_H
