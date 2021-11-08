#ifndef LEVEL_H
#define LEVEL_H

#include <QTimer>
#include <fstream>
#include "alias.h"

class Level : public QObject {
 public:
	void start();

	static Level LVL1;
	static Level LVL2;
	static Level LVL3;

 private:
	Level(const QString&);

	List<QString> instructions;
	QTimer timer;
	int waitTimer;

	void iterate();
};

#endif  // LEVEL_H
