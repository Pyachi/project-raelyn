#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QTimer>

class Packet;

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static void sendPacket(const QString&);
	static void disconnect();

 private:
	Connection();

	void handlePacket();

	static Connection* CON;
};

#endif  // CONNECTION_H
