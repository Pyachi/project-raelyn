#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>
#include <QSet>

class Server : public QTcpServer {
 public:
	static bool create(quint16);
	static Server* get();

 private:
	Server();

	static Server* SER;

	QSet<QTcpSocket*> sockets;

	QDialog view;
	QLabel ip;
	QLabel text;
	QLabel connections;

	void handleConnection();
	void handlePacket();
};

#endif  // SERVER_H
