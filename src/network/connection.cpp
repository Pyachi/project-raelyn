#include "connection.h"
#include <QNetworkProxy>
#include "packet.h"
#include "src/ai/enemy.h"
#include "src/entity/entityenemy.h"
#include "src/entity/entityplayer.h"
#include "src/framework/game.h"
#include "src/framework/menu.h"
#include "user.h"

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
	connect(this, &Connection::readyRead, [this]() {
		for (Packet packet : Packet::decode(readAll()))
			handlePacket(packet);
	});
	connect(this, &Connection::stateChanged, [this]() {
		if (this->state() == UnconnectedState) {
			if (Game::GAME == nullptr) {
				Menu::MENU->openMultiplayer();
				return;
			}
			Game::GAME->paused = true;
			Game::GAME->popupText.setText("ERROR: Disconnected from Server!");
			Game::GAME->popup.show();
		}
	});
}

void Connection::handlePacket(const Packet& packet) {
	Header header = packet.header;
	switch (header) {
		case PACKETPLAYOUTSTARTGAME:
			Game::create();
			Menu::closeMenu();
			new EntityPlayer(User::character, User::getName(), User::getUUID());
			break;
		case PACKETPLAYOUTUPDATELOBBY:
			Menu::updatePlayerList(packet.data);
			break;
		case PACKETPLAYOUTUPDATEPLAYER:
			Game::queueEvent([packet]() {
				Game::GAME->entities[UUID::fromString(packet.data.at(0))]->setPos(
						{packet.data.at(1).toDouble(), packet.data.at(2).toDouble()});
			});
			break;
		case PACKETPLAYOUTPLAYERDEATH:
			Game::queueEvent([packet]() {
				Game::GAME->entities[UUID::fromString(packet.data.at(0))]
						->deleteLater();
			});
			break;
		case PACKETPLAYOUTPLAYERSPAWN:
			Game::queueEvent([packet]() {
				EntityPlayer* player =
						new EntityPlayer(static_cast<PlayerType>(packet.data.at(2).toInt()),
														 packet.data.at(1),
														 UUID::fromString(packet.data.at(0)),
														 ONLINEPLAYER);
				player->setOpacity(0.25);
				player->hitbox.hide();
			});
			break;
		case PACKETPLAYOUTFIREBULLETS:
			Game::queueEvent([packet]() {
				EntityPlayer* player = dynamic_cast<EntityPlayer*>(
						Game::GAME->entities[UUID::fromString(packet.data.at(0))]);
				Players::getShootingPattern(player->playerType,
																		packet.data.at(1).toInt(),
																		packet.data.at(2).toInt())(player);
			});
			break;
		case PACKETPLAYOUTSPAWNENEMY:
			Game::queueEvent([packet]() {
				Enemies::spawn(static_cast<Enemy>(packet.data.at(1).toInt()),
											 UUID::fromString(packet.data.at(0)),
											 QPointF(packet.data.at(2).toDouble(),
															 packet.data.at(3).toDouble()));
			});
			break;
		case PACKETPLAYOUTENEMYDEATH:
			Game::queueEvent([packet]() {
				dynamic_cast<EntityEnemy*>(
						Game::GAME->entities[UUID::fromString(packet.data.at(0))])->kill();
			});
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
			break;
	}
}
