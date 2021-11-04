#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static void disconnect();

	static void sendPacket(const QString&);
	static void sendPacket(const QString&, const QString&);
	static void sendPacket(const QString&, const QStringList&);

 private:
	Connection();

	void handlePacket();

	static Connection* CON;
};

#endif  // CONNECTION_H
