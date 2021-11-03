#include "server.h"
#include <QDebug>
#include <QGridLayout>
#include <QHostInfo>
#include <QNetworkInterface>
#include "src/menu/multiplayermenu.h"
#include <QTcpSocket>

Server* Server::SERVER = nullptr;

bool Server::setup(quint16 port) {
	Server::SERVER = new Server();
	Server* server = Server::SERVER;

	if (!server->listen(QHostAddress::Any, port))
		return false;

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
	Server::SERVER = this;
	QGridLayout* layout = new QGridLayout;
	view.setLayout(layout);

	layout->addWidget(&ip, 1, 1, 1, -1);
	layout->addWidget(&text, 2, 1, 1, 1);
	layout->addWidget(&connections, 2, 2, 1, 1);

	QTcpServer::connect(
			this, &Server::newConnection, this, &Server::incrementCounter);
}

void Server::incrementCounter() {
	QTcpSocket* socket = nextPendingConnection();
	if (!socket)
		return;

	qDebug() << "Connection Established";
	connections.setNum(connections.text().toInt() + 1);
}
