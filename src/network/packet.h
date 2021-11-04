#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QStringList>

enum Header {
	PACKETPLAYINCONNECT,
	PACKETPLAYINDISCONNECT,
	PACKETPLAYINUPDATELOBBY,
	PACKETPLAYINSTARTGAME,
	PACKETPLAYINUPDATEPLAYER,
	PACKETPLAYOUTUPDATELOBBY,
	PACKETPLAYOUTSTARTGAME,
	PACKETPLAYOUTUPDATEPLAYER
};

class Packet {
 public:
	Packet(const Header&, const QStringList& = QStringList());

	Header header;
	QStringList data;

	QByteArray encode() const;
	static QList<Packet> decode(const QByteArray&);
};
#endif  // PACKET_H
