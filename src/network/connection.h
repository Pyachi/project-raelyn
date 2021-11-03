#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QTimer>

class Packet;

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static Connection* get();

	void sendPacket(const Packet&);

 private:
	Connection();

	static Connection* CON;
};

#endif  // CONNECTION_H
