#include "user.h"
#include <QDir>
#include <QNetworkInterface>

const QString User::name = QDir::homePath().split('/').last() + "|" +
													 QString::number((rand() % 9000) + 1000);

const QString User::getIp() {
	QString localIPAddress;
	foreach(const QHostAddress & address, QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol &&
				address.isLoopback() == false) {
			localIPAddress = address.toString();
		}
	}
	return localIPAddress;
}
