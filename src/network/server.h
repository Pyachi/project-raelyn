#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>
#include "level.h"

class Packet;
class UID;

class Server : public QTcpServer {
 public:
	static bool create(unsigned short port);
	static void destruct(void);
	static unsigned short getPort(void);

	static void sendPacket(const Packet& packet, QTcpSocket* sender = nullptr);

 private:
	Server(void);

	static Server* SER;

	QSet<QTcpSocket*> sockets;
	QMap<QTcpSocket*, UID> users;
	QMap<QTcpSocket*, QString> names;

	void handleConnection(void);
	void handleDisconnection(void);
	void receivePacket(void);
	void handlePacket(const Packet& packet, QTcpSocket* sender = nullptr);
};

#endif  // SERVER_H
