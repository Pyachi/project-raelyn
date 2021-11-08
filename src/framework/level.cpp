#include "level.h"
#include "src/network/server.h"
#include "src/network/packet.h"
#include "src/network/uuid.h"
#include "src/assets/music.h"
#include <QFile>

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
		QString instruction = instructions.front();
		instructions.pop_front();
		QStringList list = instruction.split(':');
		QString opCode = list.at(0);
		if (opCode == "WAIT") {
			waitTimer = list.at(1).toInt();
			return;
		} else if (opCode == "SPAWN") {
			Server::sendPacket({PACKETPLAYOUTSPAWNENEMY,
													QStringList() << UUID().toString() << list.at(1)
																				<< list.at(2) << list.at(3)});
		} else if (opCode == "PLAY") {
			Music::playSong(static_cast<Song>(list.at(1).toInt()), 1);
		} else if (opCode == "PAUSE") {
			waitTimer = 999;
			return;
		}
	}
}
