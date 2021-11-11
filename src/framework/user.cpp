#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include "src/network/uid.h"

namespace User {
namespace {
QString name;
QString ip;
UID id;
bool nameExists = false;
bool ipExists = false;
bool uuidExists = false;
}  // namespace

PlayerType character = PYACHI;

Array<int> keys = {Qt::Key_Up,    Qt::Key_Left, Qt::Key_Down, Qt::Key_Right,
									 Qt::Key_Shift, Qt::Key_Z,    Qt::Key_X};

int getKeyUp(void) {
	return keys[0];
};
int getKeyLeft(void) {
	return keys[1];
};
int getKeyDown(void) {
	return keys[2];
};
int getKeyRight(void) {
	return keys[3];
};
int getKeyFocus(void) {
	return keys[4];
};
int getKeyShoot(void) {
	return keys[5];
};
int getKeyBomb(void) {
	return keys[6];
};

const QString getName(void) {
	if (!nameExists) {
		name = (QDir::homePath().split('/').last() + "#" +
						QString::number((Random::getInt() % 9000) + 1000));
		nameExists = true;
	}
	return name;
}

const QString getIp(void) {
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

const UID getUUID(void) {
	if (!uuidExists) {
		id = UID();
		uuidExists = true;
	}
	return id;
}
}  // namespace User