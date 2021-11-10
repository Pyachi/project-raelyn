#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>

class Packet;
class UUID;

class Server : public QTcpServer {
 public:
	static bool create(quint16);
	static void destruct(void);
	static unsigned short getPort(void);

	static void sendPacket(const Packet&, QTcpSocket* = nullptr);

 private:
	Server(void);

	static Server* SER;

	QSet<QTcpSocket*> sockets;
	QMap<QTcpSocket*, UUID> users;
	QMap<QTcpSocket*, QString> names;

	void handleConnection(void);
	void handleDisconnection(void);

	void receivePacket(void);
	void handlePacket(const Packet&, QTcpSocket* = nullptr);
};

#endif  // SERVER_H
