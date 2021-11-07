#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include "packet.h"
#include <thread>
#include <queue>

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static bool exists();
	static void disconnect();

	static void sendPacket(const Packet&);

 private:
	Connection();

	static Connection* CON;

	void receivePacket();
	void handlePacket(const Packet&);
};

#endif  // CONNECTION_H
