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
	static ulong size() { return SER->users.size(); }

	static void sendPacket(const Packet& packet, QTcpSocket* sender = nullptr);

 private:
	Server(void);

	static Server* SER;

	QSet<QTcpSocket*> sockets;
	Map<QTcpSocket*, UID> users;
	Map<QTcpSocket*, QString> names;
	Map<QTcpSocket*, bool> ready;

	bool running;

	void start(void);

	const QStringList getNames() {
		QStringList list;
		for (auto user : names) {
			QString name = user.second;
			if (ready.at(user.first))
				name += " ✓";
			list << name;
		}
		return list;
	}

	void handleConnection(void);
	void handleDisconnection(void);
	void receivePacket(void);
	void handlePacket(const Packet& packet, QTcpSocket* sender = nullptr);
};

#endif  // SERVER_H
