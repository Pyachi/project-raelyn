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
	QSqlDatabase start_connection(QString type,
																QString host,
																int port,
																QString name,
																QString user,
																QString pass);
	QSqlDatabase start_connection(QString type);

	bool add_score(QString level, QString user, QDateTime time, int score);

	Scoreboard* get_scoreboard(QString level);

	bool update_database(QString name, Scoreboard* score);
	bool create_level_table(QString level);
	bool create_settings_table(int SFX, int music, int controls, int character);
	void update_settings(int SFX, int music, int controls, int character);
	int get_SFX();
	int get_music();
	int get_controls();
	int getCharacter(void);
	void close_database();

	bool create_master_table(QString level);  // is this needed?
	int run_table_stats(QString level);       // create object to have stats in

 private:
	QSqlDatabase db;
};

#endif  // DATABASE_API_H
