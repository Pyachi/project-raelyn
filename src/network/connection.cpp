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
    CON->sendPacket({PACKETPLAYINCONNECT,
                     QStringList() << User::getUID().toString()
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
    case PACKETPLAYOUTSTARTGAME:
      Game::create();
      Menu::MENU->close();
      new EntityPlayer(Character::valueOf(User::getCharacter()),
											 User::getName(),
											 User::getUID());
      break;
    case PACKETPLAYOUTPLAYERJOIN:
      Menu::MENU->players.clear();
      for (const QString& name : packet.data)
        Menu::MENU->players.addItem(name);
      SFX::CONNECT.play();
      break;
    case PACKETPLAYOUTPLAYERLEAVE:
      Menu::MENU->players.clear();
      for (const QString& name : packet.data)
        Menu::MENU->players.addItem(name);
      SFX::DISCONNECT.play();
      break;
    case PACKETPLAYOUTUPDATEPLAYER:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					game.getEntities().at(UID::fromString(packet.data.at(0)))->setPos(
							{packet.data.at(1).toDouble(), packet.data.at(2).toDouble()});
			}});
      break;
    case PACKETPLAYOUTPLAYERDEATH:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					game.getEntities()
							.at(UID::fromString(packet.data.at(0)))
							->deleteLater();
			}});
      break;
    case PACKETPLAYOUTPLAYERSPAWN:
			Game::queueEvent({[packet](Game&) {
				new EntityPlayer(Character::valueOf(packet.data.at(2).toInt()),
												 packet.data.at(1).toStdString(),
												 UID::fromString(packet.data.at(0)),
												 ONLINEPLAYER);
			}});
      break;
    case PACKETPLAYOUTFIREBULLETS:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0)))) {
					EntityPlayer* player = dynamic_cast<EntityPlayer*>(
							game.getEntities().at(UID::fromString(packet.data.at(0))));
					player->focus = packet.data.at(1).toInt();
					player->fireBullets(player->character.pattern(player));
				}
			}});
      break;
    case PACKETPLAYOUTSPAWNENEMY:
			Game::queueEvent({[packet](Game&) {
        Enemy::valueOf(packet.data.at(1).toInt())
            .spawn({packet.data.at(2).toDouble(), packet.data.at(3).toDouble()},
                   UID::fromString(packet.data.at(0)));
			}});
      break;
    case PACKETPLAYOUTSPAWNBOSS:
			Game::queueEvent({[packet](Game&) {
        Boss::valueOf(packet.data.at(1).toInt())
            .spawn({packet.data.at(2).toDouble(), packet.data.at(3).toDouble()},
                   UID::fromString(packet.data.at(0)));
			}});
      break;
    case PACKETPLAYOUTENEMYDEATH:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					dynamic_cast<EntityEnemy*>(game.getEntities().at(UID::fromString(
																				 packet.data.at(0))))->kill();
			}});
      break;
    case PACKETPLAYOUTPLAYSONG:
      Music::valueOf(packet.data.at(0).toInt()).play();
      break;
    case PACKETPLAYOUTADVANCEPHASE:
			Game::queueEvent({[packet](Game& game) {
				if (game.getEntities().count(UID::fromString(packet.data.at(0))))
					dynamic_cast<EntityBoss*>(game.getEntities().at(UID::fromString(
																				packet.data.at(0))))->advancePhase();
			}});
			break;
		case PACKETPLAYOUTTAKEDAMAGE:
			Game::queueEvent({[packet](Game& game) {
				dynamic_cast<EntityPlayer*>(game.getEntities().at(UID::fromString(
																				packet.data.at(0))))->invFrames = 100;
			}});
      break;
		case PACKETPLAYOUTLEVELUP:
			Game::queueEvent({[packet](Game& game) {
				dynamic_cast<EntityPlayer*>(
						game.getEntities().at(UID::fromString(packet.data.at(0))))->level++;
			}});
			break;
		default:
			qDebug() << "ERROR: Received IN Packet!";
      break;
  }
}
