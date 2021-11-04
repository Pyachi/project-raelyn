#include "connection.h"
#include <QNetworkProxy>
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
		con->sendPacket("connect", QDir::home().path().split("/").last());
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
		CON->write((packet + ";").toUtf8());
}

void Connection::sendPacket(const QString& header, const QString& data) {
	sendPacket(header + ":" + data);
}

void Connection::sendPacket(const QString& header, const QStringList& data) {
	sendPacket(header, data.join(":"));
}

void Connection::handlePacket() {
	QString data = QString(readAll());
	foreach(QString packet, data.split(";")) {
		if (packet == "")
			continue;
		QString header = packet.split(':').first();
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
