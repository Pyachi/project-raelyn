#include "server.h"
#include "user.h"
#include "packet.h"
#include "uuid.h"
#include "src/framework/game.h"
#include "src/framework/menu.h"
#include "src/framework/level.h"
#include "src/ai/enemyai.h"
#include <QGridLayout>
#include <QNetworkInterface>
#include <QTcpSocket>

Server* Server::SER = nullptr;

bool Server::create(quint16 port) {
	if (SER != nullptr)
		return false;
	Server::SER = new Server;
	Server* server = Server::SER;

	if (!server->listen(QHostAddress::Any, port)) {
		SER = nullptr;
		return false;
	}
	return true;
}

void Server::disconnect() {
	if (SER == nullptr)
		return;
	SER->close();
	SER->deleteLater();
	SER = nullptr;
}

int Server::getPort() {
	if (SER == nullptr)
		return 0;
	return SER->serverPort();
}

void Server::sendPacket(const Packet& packet, QTcpSocket* sender) {
	if (SER == nullptr)
		return;
	for (QTcpSocket* socket : SER->sockets) {
		if (sender != socket)
			socket->write(packet.encode());
	}
}

Server::Server() : QTcpServer() {
	connect(this, &Server::newConnection, this, &Server::handleConnection);
}

void Server::handleConnection() {
	QTcpSocket* socket = nextPendingConnection();
	sockets.insert(socket);
	connect(socket, &QTcpSocket::readyRead, this, &Server::receivePacket);
	connect(
			socket, &QTcpSocket::disconnected, this, &Server::handleDisconnection);
	Menu::updatePlayerCount(sockets.size());
}

void Server::handleDisconnection() {
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	sockets.remove(socket);
	users.remove(socket);
	names.remove(socket);
	Menu::updatePlayerCount(sockets.size());
	sendPacket({PACKETPLAYOUTUPDATELOBBY, names.values()});
}

void Server::receivePacket() {
	QTcpSocket* sent = qobject_cast<QTcpSocket*>(sender());
	for (Packet packet : Packet::decode(sent->readAll()))
		handlePacket(packet, sent);
}

void Server::handlePacket(const Packet& packet, QTcpSocket* sender) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYINCONNECT:
			users.insert(sender, UUID::fromString(packet.data.at(0)));
			names.insert(sender, packet.data.at(1));
			break;
		case PACKETPLAYINDISCONNECT:
			break;
		case PACKETPLAYINUPDATELOBBY:
			sendPacket({PACKETPLAYOUTUPDATELOBBY, names.values()});
			break;
		case PACKETPLAYINSTARTGAME:
			pauseAccepting();
			sendPacket(PACKETPLAYOUTSTARTGAME);
			Level::LVL1.start();
			break;
		case PACKETPLAYINUPDATEPLAYER:
			sendPacket({PACKETPLAYOUTUPDATEPLAYER,
									QStringList() << users[sender].toString() << packet.data},
								 sender);
			break;
		case PACKETPLAYINPLAYERDEATH:
			sendPacket(
					{PACKETPLAYOUTPLAYERDEATH, QStringList() << users[sender].toString()},
					sender);
			break;
		case PACKETPLAYINPLAYERSPAWN:
			sendPacket({PACKETPLAYOUTPLAYERSPAWN,
									QStringList() << users[sender].toString() << names[sender]
																<< packet.data},
								 sender);
			break;
		case PACKETPLAYINFIREBULLETS:
			sendPacket({PACKETPLAYOUTFIREBULLETS,
									QStringList() << users[sender].toString() << packet.data},
								 sender);
			break;
		case PACKETPLAYINENEMYDEATH:
			sendPacket({PACKETPLAYOUTENEMYDEATH, packet.data}, sender);
			break;
		default:
			qDebug() << "ERROR: Received OUT Packet!";
			break;
	}
}
