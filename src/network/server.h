#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>
#include <QSet>
#include <QTimer>

class Server : public QTcpServer {
 public:
	static bool create(quint16);
	static void sendPacket(const QString&);

 private:
	Server();

	static Server* SER;

	QSet<QTcpSocket*> sockets;
	QMap<QTcpSocket*, QString> users;

	QDialog view;
	QLabel ip;
	QLabel text;
	QLabel connections;

	void forwardPacket(QTcpSocket*, const QString&);

	void handleConnection();
	void handleDisconnection();
	void handlePacket();
};

#endif  // SERVER_H
