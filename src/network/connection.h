#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QTcpSocket {
 public:
	static bool create(QString, quint16);
	static Connection* get();

 private:
	Connection();

	static Connection* CON;
};

#endif  // CONNECTION_H
