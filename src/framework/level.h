#ifndef LEVEL_H
#define LEVEL_H

#include <QTimer>
#include "util.h"

class Level : public QObject {
 public:
	void start(void);
	void resume(void);

	static Level LVL1;
	static Level LVL2;
	static Level LVL3;

 private:
	Level(const QString& file);

	const QString path;
	QStringList instructions;
	QTimer timer;
	int waitTimer;

	void iterate(void);
};

#endif  // LEVEL_H
