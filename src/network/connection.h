#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Packet;

class Connection : public QTcpSocket {
 public:
	static bool create(QString ip, unsigned short port);
	static void destruct(void);

	static void sendPacket(const Packet& packet);

 private:
	Connection(void);

	static Connection* CON;

	void handlePacket(const Packet& packet);
};

#endif  // CONNECTION_H
