#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Packet;

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static bool exists(void);
	static void disconnect(void);

	static void sendPacket(const Packet&);

 private:
	Connection(void);

	static Connection* CON;

	void handlePacket(const Packet&);
};

#endif  // CONNECTION_H
