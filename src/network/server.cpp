#include "server.h"
#include <QGridLayout>
#include <QNetworkInterface>
#include <QTcpSocket>
#include "src/game/game.h"
#include "user.h"

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

	server->ip.setText(User::getIp() + ":" +
										 QString::number(server->serverPort()));
	return true;
}

void Server::viewServer() {
	SER->view.show();
}

void Server::sendPacket(const Packet& packet, QTcpSocket* sender) {
	if (SER == nullptr)
		return;
	foreach (QTcpSocket* socket, SER->sockets) {
		if (sender != socket)
			socket->write(packet.encode());
	}
}

Server::Server()
		: QTcpServer(), view(), ip(), text("Players Connected:"), connections("0") {
	QGridLayout* layout = new QGridLayout;
	view.setLayout(layout);

	layout->addWidget(&ip, 1, 1, 1, -1);
	layout->addWidget(&text, 2, 1, 1, 1);
	layout->addWidget(&connections, 2, 2, 1, 1);

	view.setWindowFlags(Qt::FramelessWindowHint);

	connect(this, &Server::newConnection, this, &Server::handleConnection);
}

void Server::handleConnection() {
	QTcpSocket* socket = nextPendingConnection();
	sockets.insert(socket);
	connect(socket, &QTcpSocket::readyRead, this, &Server::receivePacket);
	connect(socket, &QTcpSocket::disconnected, this,
					&Server::handleDisconnection);
	connections.setNum(sockets.size());
}

void Server::handleDisconnection() {
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	sockets.remove(socket);
	users.remove(socket);
	connections.setNum(sockets.size());
	sendPacket({PACKETPLAYOUTUPDATELOBBY, users.values()});
}

void Server::receivePacket() {
	QTcpSocket* sent = qobject_cast<QTcpSocket*>(sender());
	foreach (Packet packet, Packet::decode(sent->readAll())) {
		handlePacket(packet, sent);
	}
}

void Server::handlePacket(const Packet& packet, QTcpSocket* sender) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYINCONNECT:
			users.insert(sender, packet.data.at(0));
			break;
		case PACKETPLAYINDISCONNECT:
			break;
		case PACKETPLAYINUPDATELOBBY:
			sendPacket({PACKETPLAYOUTUPDATELOBBY, users.values()});
			break;
		case PACKETPLAYINSTARTGAME:
			pauseAccepting();
			sendPacket(PACKETPLAYOUTSTARTGAME);
			break;
		case PACKETPLAYINUPDATEPLAYER:
			sendPacket({PACKETPLAYOUTUPDATEPLAYER, QStringList(packet.data)
																								 << users.value(sender)},
								 sender);
			break;
		case PACKETPLAYINPLAYERDEATH:
			sendPacket(
					{PACKETPLAYOUTPLAYERDEATH, QStringList() << users.value(sender)},
					sender);
			break;
		case PACKETPLAYINPLAYERSPAWN:
			sendPacket(
					{PACKETPLAYOUTPLAYERSPAWN, QStringList() << users.value(sender)},
					sender);
			break;
		default:
			qDebug() << "ERROR: Received OUT Packet!";
			break;
	}
}
