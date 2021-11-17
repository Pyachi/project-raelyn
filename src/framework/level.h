#ifndef LEVEL_H
#define LEVEL_H

#include <QTimer>
#include "util.h"

class Level : public QObject {
 public:
	static void start(void);
	static void stop(void);
	static void resume(void);

	static Level LEVEL;

 private:
	Level(const QString& file);

	const QString path;
	QStringList instructions;
	QTimer timer;
	int waitTimer;

	void iterate(void);
};

#endif  // LEVEL_H
