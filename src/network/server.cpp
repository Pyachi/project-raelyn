#include "server.h"
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

	QString localhostIP;
	foreach(const QHostAddress & address, QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol &&
				address.isLoopback() == false) {
			localhostIP = address.toString();
		}
	}

	server->ip.setText(localhostIP + ":" + QString::number(server->serverPort()));
	server->view.show();
	return true;
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
	connect(socket, &QTcpSocket::readyRead, this, &Server::handlePacket);
	connect(
			socket, &QTcpSocket::disconnected, this, &Server::handleDisconnection);
	connections.setNum(sockets.size());
}

void Server::handlePacket() {
	QTcpSocket* sent = qobject_cast<QTcpSocket*>(sender());
	QString data = QString(sent->readAll());
	foreach(QString packet, data.split(";")) {
		if (packet == "")
			continue;
		QString header = packet.split(":").first();
		if (header == "connect") {
			users.insert(sent, packet.split(":").at(1));
		} else if (header == "updateLobbyMenu") {
			sendPacket("updateLobbyMenu", QStringList(users.values()));
		}
	}
}

void Server::handleDisconnection() {
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	sockets.remove(socket);
	users.remove(socket);
	connections.setNum(sockets.size());
	sendPacket("updateLobbyMenu:" + QStringList(users.values()).join(":") + ";");
}

void Server::sendPacket(const QString& packet) {
	if (SER != nullptr)
		foreach(QTcpSocket * socket, SER->sockets) {
			socket->write((packet + ";").toUtf8());
		}
}

void Server::sendPacket(const QString& header, const QString& data) {
	sendPacket(header + ":" + data);
}

void Server::sendPacket(const QString& header, const QStringList& data) {
	sendPacket(header, data.join(":"));
}

void Server::forwardPacket(QTcpSocket* sentFrom, const QString& packet) {
	foreach(QTcpSocket * socket, sockets) {
		if (socket != sentFrom)
			socket->write(packet.toUtf8());
	}
}
