#include "connection.h"
#include <QNetworkProxy>
#include "boss.h"
#include "enemy.h"
#include "entityboss.h"
#include "entityenemy.h"
#include "entityplayer.h"
#include "game.h"
#include "menu.h"
#include "music.h"
#include "packet.h"
#include "sfx.h"
#include "user.h"

Connection* Connection::CON = nullptr;

bool Connection::create(QString ip, unsigned short port) {
  if (CON != nullptr)
    return false;
  CON = new Connection;

  CON->connectToHost(ip, port);
  if (CON->waitForConnected(100)) {
		CON->sendPacket(
				{S_CONNECT, QStringList() << User::getUID().toString()
																	<< QString::fromStdString(User::getName())});
    CON->connect(CON, &Connection::stateChanged, []() {
      if (CON == nullptr)
        return;
      if (CON->state() == UnconnectedState) {
        Menu::MENU->lobbyMenu.hide();
        Menu::MENU->multiplayerMenu.show();
        SFX::DISCONNECT.play();
        destruct();
				Game::pause();
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
    for (const Packet& packet : Packet::decode(readAll()))
      handlePacket(packet);
  });
}

void Connection::handlePacket(const Packet& packet) {
  Header header = packet.header;
  switch (header) {
		case C_SOUND:
			if (packet.data.length() == 2)
				SFX::valueOf(packet.data.at(0).toInt()).play(packet.data.at(1).toInt());
			else
				SFX::valueOf(packet.data.at(0).toInt()).play();
      break;
		case C_SONG:
			Music::valueOf(packet.data.at(0).toInt()).play();
      break;
		case C_LOBBY:
			Menu::MENU->players.clear();
			for (const QString& name : packet.data)
				Menu::MENU->players.addItem(name);
      break;
		case C_START:
			Game::create();
			Menu::MENU->close();
			new EntityPlayer(Character::valueOf(User::getCharacter()),
											 User::getName(),
											 User::getUID());
      break;
		case C_UPDATELOC:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					game.getEntities().at(UID::fromString(packet.data.at(0)))->setPos(
							{packet.data.at(1).toDouble(), packet.data.at(2).toDouble()});
			}});
      break;
		case C_KILLPLAYER:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					game.getEntities()
							.at(UID::fromString(packet.data.at(0)))
							->deleteLater();
			}});
			break;
		case C_SPAWNPLAYER:
			Game::queueEvent({[packet](Game&) {
				new EntityPlayer(Character::valueOf(packet.data.at(2).toInt()),
												 packet.data.at(1).toStdString(),
												 UID::fromString(packet.data.at(0)),
												 ONLINEPLAYER);
			}});
			break;
		case C_SHOOT:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0)))) {
					EntityPlayer* player = dynamic_cast<EntityPlayer*>(
							game.getEntities().at(UID::fromString(packet.data.at(0))));
					player->focus = packet.data.at(1).toInt();
					player->fireBullets(player->character.pattern(player));
				}
			}});
			break;
		case C_SPAWNENEMY:
			Game::queueEvent({[packet](Game&) {
        Enemy::valueOf(packet.data.at(1).toInt())
            .spawn({packet.data.at(2).toDouble(), packet.data.at(3).toDouble()},
									 UID::fromString(packet.data.at(0)),
									 packet.data.at(4).toInt());
			}});
      break;
		case C_SPAWNBOSS:
			Game::queueEvent({[packet](Game&) {
        Boss::valueOf(packet.data.at(1).toInt())
            .spawn({packet.data.at(2).toDouble(), packet.data.at(3).toDouble()},
									 UID::fromString(packet.data.at(0)),
									 packet.data.at(4).toInt());
			}});
      break;
		case C_KILLENEMY:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					dynamic_cast<EntityEnemy*>(game.getEntities().at(UID::fromString(
																				 packet.data.at(0))))->kill();
			}});
      break;
		case C_DAMAGEBOSS:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					dynamic_cast<EntityBoss*>(game.getEntities().at(UID::fromString(
																				packet.data.at(0))))->advancePhase();
			}});
      break;
		case C_DAMAGEPLAYER:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0)))) {
					EntityPlayer* player = dynamic_cast<EntityPlayer*>(
							game.getEntities().at(UID::fromString(packet.data.at(0))));
					player->invFrames = 150;
					player->level = 1;
				}
			}});
			break;
		case C_LEVELUP:
			Game::queueEvent({[packet](Game& game) {
				dynamic_cast<EntityPlayer*>(
						game.getEntities().at(UID::fromString(packet.data.at(0))))->level++;
			}});
			break;
		default:
			qDebug() << "ERROR: Received Server Packet!";
      break;
  }
}
