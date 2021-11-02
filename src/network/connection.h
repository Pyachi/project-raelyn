#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket {
 public:
	Connection(QString, quint16);

	void printState(SocketState);
};

#endif  // CONNECTION_H
