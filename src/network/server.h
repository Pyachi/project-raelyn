#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>

class Server : public QTcpServer {
 public:
	static bool create(quint16);

	static void sendPacket(const QString&);
	static void sendPacket(const QString&, const QString&);
	static void sendPacket(const QString&, const QStringList&);

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
