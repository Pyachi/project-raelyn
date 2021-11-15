#include "level.h"
#include <QFile>
#include "packet.h"
#include "server.h"
#include "uid.h"

Level::Level(const QString& path) : path(path) {
  timer.connect(&timer, &QTimer::timeout, [this]() { this->iterate(); });
}

Level Level::LVL1("assets/levels/lvl1.txt");
Level Level::LVL2("assets/levels/lvl2.txt");
Level Level::LVL3("assets/levels/lvl3.txt");

void Level::start(void) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly))
    qDebug() << file.errorString();
  QTextStream in(&file);
  while (!in.atEnd())
    instructions.push_back(in.readLine().split('/').at(0));
  timer.start(1000 / 20);
}

void Level::resume(void) {
  waitTimer = 0;
}

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
      Server::sendPacket({PACKETPLAYOUTSPAWNENEMY,
                          QStringList() << UID().toString() << args.at(1)
                                        << args.at(2) << args.at(3)});
    } else if (opCode == "BOSS") {
      Server::sendPacket({PACKETPLAYOUTSPAWNBOSS,
                          QStringList() << UID().toString() << args.at(1)
                                        << args.at(2) << args.at(3)});
      waitTimer = -1;
      return;
    } else if (opCode == "PLAY") {
      Server::sendPacket({PACKETPLAYOUTPLAYSONG, QStringList() << args.at(1)});
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
