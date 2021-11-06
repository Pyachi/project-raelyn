#include "connection.h"
#include <QNetworkProxy>
#include "src/game.h"
#include "user.h"
#include "src/menu.h"

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	Connection::CON = new Connection;
	Connection* con = Connection::CON;

	con->connectToHost(ip, port);
	if (con->waitForConnected()) {
		con->sendPacket({PACKETPLAYINCONNECT, QStringList() << User::getName()});
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
	foreach(Packet packet, Packet::decode(readAll())) { handlePacket(packet); }
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
			Game::updatePlayerLocation(
					packet.data.at(2),
					QPointF(packet.data.at(0).toDouble(), packet.data.at(1).toDouble()));
			break;
		case PACKETPLAYOUTPLAYERDEATH:
			Game::removePlayer(packet.data.at(0));
			break;
		case PACKETPLAYOUTPLAYERSPAWN:
			Game::addPlayer(PYACHI, packet.data.at(0));
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
			break;
	}
}
