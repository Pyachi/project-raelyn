#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>

class Server : public QTcpServer {
 public:
	static bool create(quint16);
	static void viewServer();

	static void sendPacket(const QString&, QTcpSocket* = nullptr);
	static void sendPacket(const QStringList&, QTcpSocket* = nullptr);
	static void sendPacket(const QString&, const QString&, QTcpSocket* = nullptr);
	static void sendPacket(const QString&,
												 const QStringList&,
												 QTcpSocket* = nullptr);

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
	void handlePacket(QStringList&, QTcpSocket* = nullptr);
	QList<QStringList> decodePacket(const QByteArray&);
};

#endif  // SERVER_H
