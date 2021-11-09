#include "user.h"
#include <QDir>
#include <QNetworkInterface>
#include "uuid.h"

namespace User {
namespace {
QString name;
QString ip;
UUID id;
bool nameExists = false;
bool ipExists = false;
bool uuidExists = false;
}  // namespace

PlayerType character = PYACHI;

Array<int> keys = {Qt::Key_Up,    Qt::Key_Left, Qt::Key_Down, Qt::Key_Right,
									 Qt::Key_Shift, Qt::Key_Z,    Qt::Key_X};

int getKeyUp() {
	return keys[0];
};
int getKeyLeft() {
	return keys[1];
};
int getKeyDown() {
	return keys[2];
};
int getKeyRight() {
	return keys[3];
};
int getKeyFocus() {
	return keys[4];
};
int getKeyShoot() {
	return keys[5];
};
int getKeyBomb() {
	return keys[6];
};

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
}  // namespace User
