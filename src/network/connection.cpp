#include "connection.h"
#include <QDebug>
#include <QNetworkProxy>
#include "connection.h"
#include "src/menu/lobbymenu.h"
#include <QDir>

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	Connection::CON = new Connection;
	Connection* con = Connection::CON;

	con->connectToHost(ip, port);
	if (con->waitForConnected()) {
		con->write("connect:" + QDir::home().path().split("/").last().toUtf8() +
							 ";");
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

void Connection::sendPacket(const QString& packet) {
	if (CON != nullptr)
		CON->write(packet.toUtf8());
}

void Connection::handlePacket() {
	QString data = QString(readAll());
	foreach(QString packet, data.split(";")) {
		if (packet == "")
			continue;
		QString header = packet.split(':').first();
		qDebug() << "Connection::" + packet;
		if (header == "updateLobbyMenu") {
			QStringList list = packet.split(':');
			list.removeAt(0);
			LobbyMenu::setPlayers(list);
		}
	}
}

Connection::Connection() : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
	connect(this, &Connection::readyRead, this, &Connection::handlePacket);
}
