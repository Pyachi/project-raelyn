#include "connection.h"
#include <QDebug>
#include <QNetworkProxy>
#include "connection.h"

Connection::Connection(QString ip, quint16 port) : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
	connect(this, &Connection::stateChanged, this, &Connection::printState);
	connectToHost(ip, port);
}

void Connection::printState(SocketState state) {
	qDebug() << state;
}
