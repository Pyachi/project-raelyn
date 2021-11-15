#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QStringList>

enum Header {
	//***************************************************************************
	// CLIENT -> SERVER
	PACKETPLAYINCONNECT,       // UUID:name
	PACKETPLAYINPLAYERJOIN,    // null
	PACKETPLAYINSTARTGAME,     // null
	PACKETPLAYINUPDATEPLAYER,  // x:y
	PACKETPLAYINPLAYERDEATH,   // null
	PACKETPLAYINPLAYERSPAWN,   // PlayerType
	PACKETPLAYINFIREBULLETS,   // level:focus
	PACKETPLAYINENEMYDEATH,    // UUID
	PACKETPLAYINADVANCEPHASE,  // UUID
	PACKETPLAYINRESUMELEVEL,   // null
	//***************************************************************************
	// SERVER -> CLIENT
	PACKETPLAYOUTPLAYERJOIN,    // names
	PACKETPLAYOUTPLAYERLEAVE,   // names
	PACKETPLAYOUTSTARTGAME,     // null
	PACKETPLAYOUTUPDATEPLAYER,  // UUID:x:y
	PACKETPLAYOUTPLAYERDEATH,   // UUID
	PACKETPLAYOUTPLAYERSPAWN,   // UUID:name:PlayerType
	PACKETPLAYOUTFIREBULLETS,   // UUID:level:focus
	PACKETPLAYOUTSPAWNENEMY,    // UUID:EnemyType:x:y
	PACKETPLAYOUTSPAWNBOSS,     // UUID:BossType:x:y
	PACKETPLAYOUTENEMYDEATH,    // UUID
	PACKETPLAYOUTPLAYSONG,      // SONG
	PACKETPLAYOUTADVANCEPHASE,  // UUID
	//***************************************************************************
};

struct Packet {
	Packet(const Header& header, const QStringList& data = QStringList());

	Header header;
	QStringList data;

	QByteArray encode(void) const;
	static QList<Packet> decode(const QByteArray& data);
};
#endif  // PACKET_H
