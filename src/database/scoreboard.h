#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QDateTime>
#include "util.h"

struct Entry {
	Entry(QString user = "--------",
				long score = 0,
				QDateTime time = QDateTime::fromString("20010101000000",
																							 "yyyyMMddHHmmss"))
			: user(user), score(score), time(time) {}
	QString user;
	long score;
	QDateTime time;
};

class Scoreboard {
 public:
	Scoreboard() {}
	void add(const Entry& add);

	const Entry get(ulong index) const {
		return entries.size() > index ? entries.at(index) : Entry();
	}

 private:
	Array<Entry> entries;
};

#endif  // SCOREBOARD_H
