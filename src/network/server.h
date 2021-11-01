#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QLabel>
#include <QTcpServer>

class Server : public QTcpServer {
 public:
	static bool setup(quint16);

 private:
	Server();

	static Server* SERVER;

	QDialog view;
	QLabel ip;
	QLabel text;
	QLabel connections;
	void incrementCounter();
};

#endif  // SERVER_H
