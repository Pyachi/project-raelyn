#include "server.h"
#include <QGridLayout>
#include <QNetworkInterface>
#include <QTcpSocket>
#include "Network"
#include "Framework"

Server* Server::SER = nullptr;

bool Server::create(unsigned short port) {
	if (SER != nullptr)
		return false;
	Server::SER = new Server();
	Server* server = Server::SER;

	if (!server->listen(QHostAddress::Any, port)) {
		SER = nullptr;
		return false;
	}
	if (port == 0)
		port = SER->getPort();
	return true;
}

void Server::destruct(void) {
	if (SER == nullptr)
		return;
	SER->deleteLater();
	SER = nullptr;
}

unsigned short Server::getPort(void) {
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
	Menu::MENU->playerCount.setText("Players Connected: 0");
}

void Server::handleConnection(void) {
	QTcpSocket* socket = nextPendingConnection();
	sockets.insert(socket);
	connect(socket, &QTcpSocket::readyRead, this, &Server::receivePacket);
	connect(
			socket, &QTcpSocket::disconnected, this, &Server::handleDisconnection);
	Menu::MENU->playerCount.setText("Players Connected: " +
																	QString::number(sockets.size()));
}

void Server::handleDisconnection(void) {
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	sendPacket({PACKETPLAYOUTPLAYERDEATH, QStringList()
																						<< users.value(socket).toString()},
						 socket);
	sockets.remove(socket);
	users.remove(socket);
	names.remove(socket);
	Menu::MENU->playerCount.setText("Players Connected: " +
																	QString::number(sockets.size()));
	sendPacket({PACKETPLAYOUTPLAYERLEAVE, names.values()});
	if (sockets.size() == 0 && !isListening()) {
		Menu::MENU->serverStatus.setText("Status: In Lobby");
		listen(QHostAddress::Any, Menu::MENU->portForm.text().toUShort());
	}
}

void Server::receivePacket(void) {
	QTcpSocket* sent = qobject_cast<QTcpSocket*>(sender());
	for (Packet packet : Packet::decode(sent->readAll()))
		handlePacket(packet, sent);
}

void Server::handlePacket(const Packet& packet, QTcpSocket* sender) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYINCONNECT:
			users.insert(sender, UID::fromString(packet.data.at(0)));
			names.insert(sender, packet.data.at(1));
			break;
		case PACKETPLAYINPLAYERJOIN:
			sendPacket({PACKETPLAYOUTPLAYERJOIN, names.values()});
			break;
		case PACKETPLAYINSTARTGAME:
			Menu::MENU->serverStatus.setText("Status: In Game");
			close();
			sendPacket(PACKETPLAYOUTSTARTGAME);
			level = &Level::LVL1;
			level->start();
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
		case PACKETPLAYINADVANCEPHASE:
			sendPacket({PACKETPLAYOUTADVANCEPHASE, packet.data}, sender);
			break;
		case PACKETPLAYINRESUMELEVEL:
			level->resume();
			break;
		default:
			qDebug() << "ERROR: Received OUT Packet!";
			break;
	}
}
