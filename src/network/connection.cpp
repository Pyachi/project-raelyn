#include "connection.h"
#include <QDebug>
#include <QNetworkProxy>
#include "connection.h"
#include "packet/packet.h"

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	Connection::CON = new Connection;
	Connection* con = Connection::CON;

	con->connectToHost(ip, port);
	if (con->waitForConnected())
		return true;
	else {
		CON->deleteLater();
		CON = nullptr;
		return false;
	}
}

void Connection::sendPacket(const Packet& packet) {
	write(packet.encode().toUtf8());
}

Connection* Connection::get() { return CON; }

Connection::Connection() : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
}
