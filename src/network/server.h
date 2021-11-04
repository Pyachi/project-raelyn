#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>
#include "packet.h"

class Server : public QTcpServer {
 public:
	static bool create(quint16);
	static void viewServer();

	static void sendPacket(const Packet&, QTcpSocket* = nullptr);

 private:
	Server();

	static Server* SER;

	QSet<QTcpSocket*> sockets;
	QMap<QTcpSocket*, QString> users;

	QDialog view;
	QLabel ip;
	QLabel text;
	QLabel connections;

	void handleConnection();
	void handleDisconnection();

	void receivePacket();
	void handlePacket(const Packet&, QTcpSocket* = nullptr);
};

#endif  // SERVER_H
