#include "connection.h"
#include <QDebug>
#include <QNetworkProxy>
#include "connection.h"

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	Connection::CON = new Connection;
	Connection* con = Connection::CON;

	con->connectToHost(ip, port);
	if (con->waitForConnected()) {
		con->write("test");
		return true;
	} else {
		CON = nullptr;
		return false;
	}
}

Connection* Connection::get() { return CON; }

Connection::Connection() : QTcpSocket() { setProxy(QNetworkProxy::NoProxy); }
