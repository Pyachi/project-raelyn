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

class Database {
 public:
	Database();
    ~Database();
    Database(QString use);

	bool add(QString user, QDateTime time, long score);

	Scoreboard* getScoreboard();
	Scoreboard* getScoreboard(QString use);

	bool update(Scoreboard* score);
	bool createLevelTable();
	bool createSettingsTable(int SFX, int music, int controls, int character);
	void updateSettings(int SFX, int music, int controls, int character);
	int getSFXVol();
	int getMusicVol();
	int getControls();
	int getCharacter(void);
	void close();

	void updateNetwork(QString ip, unsigned short port);
	const QString getIP();
	const QString getPort();

    QSqlDatabase getDatabase();

 private:
	QString user;
	QSqlDatabase db;
};

#endif  // DATABASE_API_H
