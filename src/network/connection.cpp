#include "connection.h"
#include <QDir>
#include <QNetworkProxy>
#include "src/game/game.h"
#include "src/menu/lobbymenu.h"
#include "src/menu/singleplayermenu.h"

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
	if (CON == nullptr)
		return;
	CON->write((packet + ";").toUtf8());
}

void Connection::sendPacket(const QStringList& packet) {
	sendPacket(packet.join(":"));
}

void Connection::sendPacket(const QString& header, const QString& data) {
	sendPacket(header + ":" + data);
}

void Connection::sendPacket(const QString& header, const QStringList& data) {
	sendPacket(header, data.join(":"));
}

Connection::Connection() : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
	connect(this, &Connection::readyRead, this, &Connection::receivePacket);
}

void Connection::receivePacket() {
	foreach (QStringList packet, decodePacket(readAll())) {
		handlePacket(packet);
	}
}

void Connection::handlePacket(QStringList& packet) {
	QString header = packet.first();
	if (header == "updateLobbyMenu") {
		packet.removeAt(0);
		LobbyMenu::setPlayers(packet);
	} else if (header == "startGame") {
		Game::create();
		SingleplayerMenu::closeMenu();
		LobbyMenu::closeMenu();
	} else if (header == "playerLocation") {
		Game::updatePlayerLocation(
				packet.at(3), QPointF(packet.at(1).toFloat(), packet.at(2).toFloat()));
	}
}

QList<QStringList> Connection::decodePacket(const QByteArray& data) {
	QList<QStringList> list;
	foreach (QString packet, data.split(';')) { list.append(packet.split(':')); }
	return list;
}
