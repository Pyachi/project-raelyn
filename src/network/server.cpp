#include "server.h"
#include <QGridLayout>
#include <QNetworkInterface>
#include <QTcpSocket>
#include "menu.h"
#include "packet.h"
#include "uid.h"
#include "sfx.h"

Server* Server::SER = nullptr;

bool Server::create(unsigned short port) {
  if (SER != nullptr)
    return false;
  Server::SER = new Server();
  Server* server = Server::SER;

  if (!server->listen(QHostAddress::Any, port)) {
    SER = nullptr;
    return false;
  }
  if (port == 0)
    port = SER->getPort();
  return true;
}

void Server::destruct(void) {
  if (SER == nullptr)
    return;
  SER->deleteLater();
	Level::stop();
  SER = nullptr;
}

unsigned short Server::getPort(void) {
  if (SER == nullptr)
    return 0;
  return SER->serverPort();
}

void Server::sendPacket(const Packet& packet, QTcpSocket* sender) {
  if (SER == nullptr)
    return;
  for (QTcpSocket* socket : SER->sockets) {
    if (sender != socket)
      socket->write(packet.encode());
  }
}

Server::Server() : QTcpServer(), running(false) {
  connect(this, &Server::newConnection, this, &Server::handleConnection);
  Menu::MENU->playerCount.setText("Players Connected: 0");
}

void Server::handleConnection(void) {
  QTcpSocket* socket = nextPendingConnection();
  sockets.insert(socket);
  connect(socket, &QTcpSocket::readyRead, this, &Server::receivePacket);
	connect(
			socket, &QTcpSocket::disconnected, this, &Server::handleDisconnection);
  Menu::MENU->playerCount.setText("Players Connected: " +
                                  QString::number(sockets.size()));
}

void Server::handleDisconnection(void) {
  QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
	sendPacket({C_KILLPLAYER, QStringList() << users.at(socket).toString()},
						 socket);
  sockets.remove(socket);
	users.erase(socket);
	names.erase(socket);
	ready.erase(socket);
  Menu::MENU->playerCount.setText("Players Connected: " +
                                  QString::number(sockets.size()));
	sendPacket({C_LOBBY, getNames()});
	sendPacket({C_SOUND, QStringList() << QString::number(SFX::DISCONNECT)});
  if (sockets.size() == 0 && !isListening()) {
    Menu::MENU->serverStatus.setText("Status: In Lobby");
		Level::stop();
		running = false;
    listen(QHostAddress::Any, Menu::MENU->portForm.text().toUShort());
	} else {
		if (running)
			return;
		for (auto pair : ready)
			if (!pair.second)
				return;
		start();
	}
}

void Server::start(void) {
	Menu::MENU->serverStatus.setText("Status: In Game");
	sendPacket(C_START);
	close();
	running = true;
	Level::start();
}

void Server::receivePacket(void) {
  QTcpSocket* sent = qobject_cast<QTcpSocket*>(sender());
  for (Packet packet : Packet::decode(sent->readAll()))
    handlePacket(packet, sent);
}

void Server::handlePacket(const Packet& packet, QTcpSocket* sender) {
  Header header = packet.header;
  switch (header) {
    case S_CONNECT:
			users.insert({sender, UID::fromString(packet.data.at(0))});
			names.insert({sender, packet.data.at(1)});
			ready.insert({sender, false});
      break;
		case S_JOIN:
			sendPacket({C_LOBBY, getNames()});
			sendPacket({C_SOUND, QStringList() << QString::number(SFX::CONNECT)});
			break;
		case S_READY:
			ready.at(sender) = true;
			sendPacket({C_LOBBY, getNames()});
			for (auto pair : ready)
				if (!pair.second)
					return;
			start();
			break;
		case S_UNREADY:
			ready.at(sender) = false;
			sendPacket({C_LOBBY, getNames()});
      break;
    case S_START:
			start();
      break;
    case S_UPDATELOC:
			sendPacket({C_UPDATELOC, QStringList() << users[sender].toString()
																						 << packet.data},
                 sender);
      break;
    case S_KILLPLAYER:
			sendPacket({C_KILLPLAYER, QStringList() << users[sender].toString()},
								 sender);
      break;
    case S_SPAWNPLAYER:
			sendPacket({C_SPAWNPLAYER, QStringList() << users[sender].toString()
																							 << names[sender] << packet.data},
                 sender);
      break;
    case S_SHOOT:
			sendPacket(
					{C_SHOOT, QStringList() << users[sender].toString() << packet.data},
					sender);
      break;
    case S_KILLENEMY:
      sendPacket({C_KILLENEMY, packet.data}, sender);
      break;
    case S_DAMAGEBOSS:
      sendPacket({C_DAMAGEBOSS, packet.data}, sender);
      break;
    case S_RESUME:
			Level::resume();
      break;
		case S_DAMAGEPLAYER:
			sendPacket({C_DAMAGEPLAYER, QStringList() << users[sender].toString()},
								 sender);
			break;
		case S_LEVELUP:
			sendPacket({C_LEVELUP, QStringList() << users[sender].toString()},
								 sender);
			break;
    default:
      qDebug() << "ERROR: Received OUT Packet!";
      break;
  }
}
