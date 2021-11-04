#include "server.h"
#include <QGridLayout>
#include <QNetworkInterface>
#include <QTcpSocket>
#include "src/game/game.h"

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

	QString localhostIP;
	foreach (const QHostAddress& address, QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol &&
				address.isLoopback() == false) {
			localhostIP = address.toString();
		}
	}

	server->ip.setText(localhostIP + ":" + QString::number(server->serverPort()));
	return true;
}

void Server::viewServer() {
	SER->view.show();
}

void Server::sendPacket(const QString& packet, QTcpSocket* sender) {
	if (SER == nullptr)
		return;
	foreach (QTcpSocket* socket, SER->sockets) {
		if (sender != socket)
			socket->write((packet + ";").toUtf8());
	}
}

void Server::sendPacket(const QStringList& packet, QTcpSocket* sender) {
	sendPacket(packet.join(":"), sender);
}

void Server::sendPacket(const QString& header,
												const QString& data,
												QTcpSocket* sender) {
	sendPacket(header + ":" + data, sender);
}

void Server::sendPacket(const QString& header,
												const QStringList& data,
												QTcpSocket* sender) {
	sendPacket(header, data.join(":"), sender);
}

Server::Server()
		: QTcpServer(), view(), ip(), text("Players Connected:"), connections("0") {
	QGridLayout* layout = new QGridLayout;
	view.setLayout(layout);

	layout->addWidget(&ip, 1, 1, 1, -1);
	layout->addWidget(&text, 2, 1, 1, 1);
	layout->addWidget(&connections, 2, 2, 1, 1);

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
	sendPacket("updateLobbyMenu:" + QStringList(users.values()).join(":") + ";");
}

void Server::receivePacket() {
	QTcpSocket* sent = qobject_cast<QTcpSocket*>(sender());
	foreach (QStringList packet, decodePacket(sent->readAll())) {
		handlePacket(packet, sent);
	}
}

void Server::handlePacket(QStringList& packet, QTcpSocket* sender) {
	QString header = packet.first();
	if (header == "connect") {
		users.insert(sender, packet.at(1));
	} else if (header == "updateLobbyMenu") {
		sendPacket("updateLobbyMenu", QStringList(users.values()));
	} else if (header == "startGame") {
		sendPacket(packet);
	} else if (header == "playerLocation") {
		packet.append(users.value(sender));
		sendPacket(packet, sender);
	}
}

QList<QStringList> Server::decodePacket(const QByteArray& data) {
	QList<QStringList> list;
	foreach (QString packet, data.split(';')) { list.append(packet.split(':')); }
	return list;
}
