#include "connection.h"
#include <QDebug>

Connection::Connection(QString ip, quint16 port) : QTcpSocket() {
	connect(this, &Connection::stateChanged, this, &Connection::printState);
	connectToHost(ip, port);
}

void Connection::printState(SocketState state) {
	qDebug() << state;
}
