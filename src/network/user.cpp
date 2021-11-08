#include "user.h"
#include "uuid.h"
#include <QDir>
#include <QNetworkInterface>

namespace User {
namespace {
QString name;
QString ip;
UUID id;
bool nameExists = false;
bool ipExists = false;
bool uuidExists = false;
}

PlayerType character = PYACHI;

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

const UUID getUUID() {
	if (!uuidExists) {
		id = UUID();
		uuidExists = true;
	}
	return id;
}
}
