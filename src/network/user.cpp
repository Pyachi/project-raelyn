#include "user.h"
#include <QDir>
#include <QNetworkInterface>

namespace User {
namespace {
QString name;
QString ip;
bool nameExists = false;
bool ipExists = false;
}

const QString getName() {
	if (!nameExists) {
		name = (QDir::homePath().split('/').last() + "#" +
						QString::number((rand() % 9000) + 1000));
		nameExists = true;
	}
	return name;
}

const QString getIp() {
	if (!ipExists) {
		for (const QHostAddress& address : QNetworkInterface::allAddresses()) {
			if (address.protocol() == QAbstractSocket::IPv4Protocol &&
					address.isLoopback() == false) {
				ip = address.toString();
				break;
			}
		}
		ipExists = true;
	}
	return ip;
}
}
