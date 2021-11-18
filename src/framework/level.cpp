#include "level.h"
#include <QFile>
#include "packet.h"
#include "server.h"
#include "uid.h"

Level::Level(const QString& path) : path(path) {
  timer.connect(&timer, &QTimer::timeout, [this]() { this->iterate(); });
}

Level Level::LEVEL(":/level.prll");

void Level::start(void) {
	QFile file(LEVEL.path);
  if (!file.open(QIODevice::ReadOnly))
    qDebug() << file.errorString();
  QTextStream in(&file);
  while (!in.atEnd())
		LEVEL.instructions.push_back(in.readLine().split('/').at(0));
	LEVEL.timer.start(1000 / 20);
}

void Level::stop(void) {
	LEVEL.instructions.clear();
	LEVEL.timer.stop();
}

void Level::resume(void) { LEVEL.waitTimer = 0; }

void Level::iterate(void) {
  if (waitTimer != 0) {
    waitTimer--;
    return;
  }
  while (!instructions.empty()) {
    QString instruction;
    instruction = instructions.front();
    instructions.pop_front();
    QStringList args = instruction.split(':');
    QString opCode = args.at(0);
    if (opCode == "WAIT") {
      waitTimer = args.at(1).toInt();
      return;
    } else if (opCode == "SPAWN") {
      Server::sendPacket({C_SPAWNENEMY,
                          QStringList() << UID().toString() << args.at(1)
                                        << args.at(2) << args.at(3)});
    } else if (opCode == "BOSS") {
      Server::sendPacket({C_SPAWNBOSS,
                          QStringList() << UID().toString() << args.at(1)
                                        << args.at(2) << args.at(3)});
      waitTimer = -1;
      return;
    } else if (opCode == "PLAY") {
      Server::sendPacket({C_SONG, QStringList() << args.at(1)});
    } else if (opCode == "PAUSE") {
      waitTimer = 999;
      return;
    } else if (opCode == "STARTLOOP") {
      int loopCount = args.at(1).toInt();
      QStringList loopInstructions;
      while (opCode != "ENDLOOP") {
        instruction = instructions.front();
        instructions.pop_front();
        args = instruction.split(':');
        opCode = args.at(0);
        loopInstructions.push_back(instruction);
      }
      QStringList loop;
      for (int i = 0; i < loopCount; i++)
        loop << loopInstructions;
      instructions = loop << instructions;
    } else if (opCode == "$") {
      while (opCode != "\\$") {
        instruction = instructions.front();
        instructions.pop_front();
        args = instruction.split(':');
        opCode = args.at(0);
      }
    }
  }
}
