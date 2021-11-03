#include "server.h"
#include <QDebug>
#include <QGridLayout>
#include <QHostInfo>
#include <QNetworkInterface>
#include "src/menu/multiplayermenu.h"
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

Server* Server::get() {
	if (!SER)
		create(0);
	return SER;
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
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	qDebug() << socket->readAll();
}

void Server::handleDisconnection() {
	QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	sockets.remove(socket);
	connections.setNum(sockets.size());
}
