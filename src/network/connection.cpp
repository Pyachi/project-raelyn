#include "connection.h"
#include <QDir>
#include <QNetworkProxy>
#include "src/game/game.h"
#include "src/menu/lobbymenu.h"
#include "src/menu/singleplayermenu.h"

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	Connection::CON = new Connection;
	Connection* con = Connection::CON;

	con->connectToHost(ip, port);
	if (con->waitForConnected()) {
		con->sendPacket(
				Packet(PACKETPLAYINCONNECT,
							 QStringList() << QDir::home().path().split('/').last()));
		return true;
	} else {
		CON->deleteLater();
		CON = nullptr;
		return false;
	}
}

void Connection::disconnect() {
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
	foreach(Packet packet, Packet::decode(readAll())) { handlePacket(packet); }
}

void Connection::handlePacket(const Packet& packet) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYOUTSTARTGAME:
			Game::create();
			SingleplayerMenu::closeMenu();
			LobbyMenu::closeMenu();
			break;
		case PACKETPLAYOUTUPDATELOBBY:
			LobbyMenu::setPlayers(packet.data);
			break;
		case PACKETPLAYOUTUPDATEPLAYER:
			Game::updatePlayerLocation(
					packet.data.at(2),
					QPointF(packet.data.at(0).toDouble(), packet.data.at(1).toDouble()));
			break;
		case PACKETPLAYOUTPLAYERDEATH:
			Game::removeOnlinePlayer(packet.data.at(0));
			break;
		case PACKETPLAYOUTPLAYERSPAWN:
			Game::addOnlinePlayer(packet.data.at(0));
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
			break;
	}
}
