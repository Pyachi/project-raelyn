#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static void disconnect();

	static void sendPacket(const QString&);
	static void sendPacket(const QStringList&);
	static void sendPacket(const QString&, const QString&);
	static void sendPacket(const QString&, const QStringList&);

 private:
	Connection();

	static Connection* CON;

	void receivePacket();
	void handlePacket(QStringList&);
	QList<QStringList> decodePacket(const QByteArray&);
};

#endif  // CONNECTION_H
