#include "connection.h"
#include <QNetworkProxy>
#include "packet.h"
#include "src/ai/enemy.h"
#include "src/assets/sfx.h"
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
		CON->connect(CON, &Connection::stateChanged, []() {
			if (CON == nullptr)
				return;
			if (CON->state() == UnconnectedState) {
				Menu::MENU->lobbyMenu.hide();
				Menu::MENU->multiplayerMenu.show();
				SFX::playSound(SFX_DISCONNECT);
				destruct();
				if (Game::GAME == nullptr)
					return;
				Game::GAME->paused = true;
				Game::GAME->popupText.setText("ERROR: Disconnected from Server!");
				Game::GAME->popup.show();
			}
		});
		return true;
	} else {
		CON->deleteLater();
		CON = nullptr;
		return false;
	}
}

void Connection::destruct(void) {
	if (CON == nullptr)
		return;
	CON->deleteLater();
	CON = nullptr;
}

void Connection::sendPacket(const Packet& packet) {
	if (CON == nullptr)
		return;
	CON->write(packet.encode());
}

Connection::Connection(void) : QTcpSocket() {
	setProxy(QNetworkProxy::NoProxy);
	connect(this, &Connection::readyRead, [this]() {
		for (Packet packet : Packet::decode(readAll()))
			handlePacket(packet);
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
		case PACKETPLAYOUTPLAYERJOIN:
			Menu::updatePlayerList(packet.data);
			SFX::playSound(SFX_CONNECT);
			break;
		case PACKETPLAYOUTPLAYERLEAVE:
			Menu::updatePlayerList(packet.data);
			SFX::playSound(SFX_DISCONNECT);
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
				if (Game::GAME->entities.contains(UUID::fromString(packet.data.at(0))))
					dynamic_cast<EntityEnemy*>(
							Game::GAME->entities[UUID::fromString(packet.data.at(0))])
							->kill();
			});
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
			break;
	}
}
