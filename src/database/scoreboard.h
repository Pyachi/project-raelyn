#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <qdebug.h>
#include <QVector>
#include <QDateTime>
class Scoreboard {
 public:
        // a struct to hold a game entry with user, score, & time
    struct Entry {
		Entry(QString user = "--------",
					long score = 0,
					QDateTime time =
							QDateTime::fromString("20010101000000", "yyyyMMddHHmmss"))
				: user(user), score(score), time(time), next(nullptr), last(nullptr) {}
		QString user;
		long score;
		QDateTime time;
		Entry* next;
		Entry* last;
	};

	Scoreboard();
	void add(QString user, QDateTime time, long score);
	void add(Entry* add);

	Scoreboard* extraHere(Scoreboard* other);
	void sort();
	int getLength();

	void show();
	Entry* get(int index);

 private:
	int length;

	void swap(Entry* left, Entry* right);
	int exists(Entry* checker);
	bool equal(Entry* A, Entry* B);

	Entry* head;
	Entry* tail;
};

#endif  // SCOREBOARD_H
