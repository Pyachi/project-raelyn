#include "level.h"
#include <QFile>
#include "src/assets/music.h"
#include "src/network/packet.h"
#include "src/network/server.h"
#include "src/network/uuid.h"

Level::Level(const QString& path) : path(path) {
	timer.connect(&timer, &QTimer::timeout, [this]() { this->iterate(); });
}

Level Level::LVL1(":/levels/lvl1.txt");
Level Level::LVL2(":/levels/lvl2.txt");
Level Level::LVL3(":/levels/lvl3.txt");

void Level::start() {
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
		qDebug() << file.errorString();
	QTextStream in(&file);
	while (!in.atEnd())
		instructions.push_back(in.readLine().split('/').at(0));
	timer.start(1000 / 20);
}

void Level::iterate() {
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
													QStringList() << UUID().toString() << args.at(1)
																				<< args.at(2) << args.at(3)});
		} else if (opCode == "PLAY") {
			Music::playSong(static_cast<Song>(args.at(1).toInt()));
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
		}
	}
}
