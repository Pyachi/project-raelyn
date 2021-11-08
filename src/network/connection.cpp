#include "connection.h"
#include "packet.h"
#include "user.h"
#include "src/game.h"
#include "src/menu.h"
#include "src/entity/player.h"
#include "src/entity/enemy.h"
#include "src/ai/enemyai.h"
#include <QNetworkProxy>

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, quint16 port) {
	if (CON != nullptr)
		return false;
	CON = new Connection;

	CON->connectToHost(ip, port);
	if (CON->waitForConnected()) {
		CON->sendPacket({PACKETPLAYINCONNECT, QStringList()
																							<< User::getUUID().toString()
																							<< User::getName()});
		return true;
	} else {
		CON->deleteLater();
		CON = nullptr;
		return false;
	}
}

bool Connection::exists() { return CON != nullptr; }

void Connection::disconnect() {
	if (CON == nullptr)
		return;
	CON->disconnectFromHost();
	CON->deleteLater();
	CON = nullptr;
}

void Connection::sendPacket(const Packet& packet) {
	if (CON == nullptr)
		return;
	CON->write(packet.encode());
}

Connection::Connection() : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
	connect(this, &Connection::readyRead, this, &Connection::receivePacket);
}

void Connection::receivePacket() {
	for (Packet packet : Packet::decode(readAll()))
		handlePacket(packet);
}

void Connection::handlePacket(const Packet& packet) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYOUTSTARTGAME:
			Game::create();
			Menu::closeMenu();
			break;
		case PACKETPLAYOUTUPDATELOBBY:
			Menu::updatePlayerList(packet.data);
			break;
		case PACKETPLAYOUTUPDATEPLAYER:
			Game::queueEvent([packet]() {
				Game::GAME->entities[UUID::fromString(packet.data.at(0))]
						->setPos(QPointF(packet.data.at(1).toDouble(),
														 packet.data.at(2).toDouble()));
			});
			break;
		case PACKETPLAYOUTPLAYERDEATH:
			// This is broken will fix later :)
			break;
		case PACKETPLAYOUTPLAYERSPAWN:
			Game::queueEvent([packet]() {
				Player* player = new Player(Players::fromInt(packet.data.at(2).toInt()),
																		packet.data.at(1),
																		UUID::fromString(packet.data.at(0)),
																		ONLINEPLAYER);
				player->setOpacity(0.25);
				player->hitbox.hide();
			});
			break;
		case PACKETPLAYOUTFIREBULLETS:
			Game::queueEvent([packet]() {
				Player* player = dynamic_cast<Player*>(
						Game::GAME->entities[UUID::fromString(packet.data.at(0))]);
				Players::getShootingPattern(player->playerType,
																		packet.data.at(1).toInt(),
																		packet.data.at(2).toInt())(player);
			});
			break;
		case PACKETPLAYOUTSPAWNENEMY:
			Game::queueEvent([packet]() {
				Enemies::get(static_cast<EnemyType>(packet.data.at(1).toInt())).spawn(
						QPointF(packet.data.at(2).toDouble(), packet.data.at(3).toDouble()),
						UUID::fromString(packet.data.at(0)));
			});
			break;
		case PACKETPLAYOUTENEMYDEATH:
			Game::queueEvent([packet]() {
				dynamic_cast<Enemy*>(
						Game::GAME->entities[UUID::fromString(packet.data.at(0))])->kill();
			});
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
			break;
	}
}
