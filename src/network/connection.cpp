#include "connection.h"
#include <QNetworkProxy>
#include "src/entity/player.h"
#include "src/game.h"
#include "src/menu.h"
#include "user.h"

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	CON = new Connection;

	CON->connectToHost(ip, port);
	if (CON->waitForConnected()) {
		CON->sendPacket({PACKETPLAYINCONNECT, QStringList() << User::getName()});
		return true;
	} else {
		CON->deleteLater();
		CON = nullptr;
		return false;
	}
}

bool Connection::exists() { return CON != nullptr; }

void Connection::disconnect() {
	if (CON == nullptr)
		return;
	CON->disconnectFromHost();
	CON->deleteLater();
	CON = nullptr;
}

void Connection::sendPacket(const Packet& packet) {
	if (CON == nullptr)
		return;
	CON->write(packet.encode());
}

Connection::Connection() : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
	connect(this, &Connection::readyRead, this, &Connection::receivePacket);
}

void Connection::receivePacket() {
	for (Packet packet : Packet::decode(readAll()))
		handlePacket(packet);
}

void Connection::handlePacket(const Packet& packet) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYOUTSTARTGAME:
			Game::create();
			Menu::closeMenu();
			break;
		case PACKETPLAYOUTUPDATELOBBY:
			Menu::updatePlayerList(packet.data);
			break;
		case PACKETPLAYOUTUPDATEPLAYER:
			Game::queueEvent([packet]() {
				Game::GAME->onlinePlayers.at(packet.data.at(2))->setPos(QPointF(
						packet.data.at(0).toDouble(), packet.data.at(1).toDouble()));
			});
			break;
		case PACKETPLAYOUTPLAYERDEATH:
			// This is broken will fix later :)
			break;
		case PACKETPLAYOUTPLAYERSPAWN:
			Game::queueEvent([packet]() {
				Player* player = new Player(PYACHI, packet.data.at(0));
				player->setOpacity(0.25);
				player->hitbox.hide();
				Game::GAME->onlinePlayers[packet.data.at(0)] = player;
			});
			break;
		case PACKETPLAYOUTFIREBULLETS:
			Game::queueEvent([packet]() {
				PlayerInfo::getShootingPattern(
						static_cast<PlayerType>(packet.data.at(1).toInt()),
						packet.data.at(2).toInt(),
						packet.data.at(3).toInt())(
						Game::GAME->onlinePlayers.at(packet.data.at(0)));
			});
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
			break;
	}
}
