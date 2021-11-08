#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QStringList>

enum Header {
	// CLIENT -> SERVER
	PACKETPLAYINCONNECT,       // UUID:name
	PACKETPLAYINDISCONNECT,    // null
	PACKETPLAYINUPDATELOBBY,   // null
	PACKETPLAYINSTARTGAME,     // null
	PACKETPLAYINUPDATEPLAYER,  // x:y
	PACKETPLAYINPLAYERDEATH,   // null
	PACKETPLAYINPLAYERSPAWN,   // PlayerType
	PACKETPLAYINFIREBULLETS,   // level:focus
	PACKETPLAYINENEMYDEATH,    // UUID

	// SERVER -> CLIENT
	PACKETPLAYOUTUPDATELOBBY,   // names
	PACKETPLAYOUTSTARTGAME,     // null
	PACKETPLAYOUTUPDATEPLAYER,  // UUID:x:y
	PACKETPLAYOUTPLAYERDEATH,   // UUID
	PACKETPLAYOUTPLAYERSPAWN,   // UUID:name:PlayerType
	PACKETPLAYOUTFIREBULLETS,   // UUID:level:focus
	PACKETPLAYOUTSPAWNENEMY,    // UUID:EnemyType:x:y
	PACKETPLAYOUTENEMYDEATH,    // UUID
};

struct Packet {
	Packet(const Header&, const QStringList& = QStringList());

	Header header;
	QStringList data;

	QByteArray encode() const;
	static QList<Packet> decode(const QByteArray&);
};
#endif  // PACKET_H
