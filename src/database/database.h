#ifndef DATABASE_API_H
#define DATABASE_API_H

#include <QDateTime>
#include <QSqlDatabase>
#include <QString>
#include "util.h"

class Scoreboard;
struct Entry;

class Database {
	Database(const QString& user)
			: user(user), db(QSqlDatabase::addDatabase("QSQLITE")) {
		atexit([]() {
			DB->db.close();
			delete DB;
		});
	}

	static Database* DB;

 public:
	static Database& create(const String& user);
	static Database& get();
	bool add(const Entry& entry);

	Scoreboard getMasterboard(void);
	Scoreboard getPlayerboard(QString use);

	void createScoreTable();
	void createSettingsTable(int SFX, int music, int controls, int character);
	void updateSettings(int SFX, int music, int controls, int character);
	int getSFXVol(void);
	int getMusicVol(void);
	int getControls(void);
	int getCharacter(void);

	void updateNetwork(QString ip, unsigned short port);
	const QString getIP(void);
	const QString getPort(void);

	QSqlDatabase& getDatabase(void) { return DB->db; }

 private:
	const QString user;
	QSqlDatabase db;
};

#endif  // DATABASE_API_H
