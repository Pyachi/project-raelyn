#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QStringList>

enum Header {
	//***************************************************************************
	// CLIENT -> SERVER
	S_CONNECT,       // UUID:name
	S_JOIN,          // null
	S_READY,         // null
	S_UNREADY,       // null
	S_START,         // null
	S_UPDATELOC,     // x:y
	S_KILLPLAYER,    // null
	S_SCORE,         // score
	S_SPAWNPLAYER,   // PlayerType
	S_SHOOT,         // focus
	S_KILLENEMY,     // UUID
	S_DAMAGEBOSS,    // UUID:phase
	S_RESUME,        // null
	S_DAMAGEPLAYER,  // null
	S_LEVELUP,       // null
	S_BOMB,          // null
	//***************************************************************************
	// SERVER -> CLIENT
	C_SOUND,         // SFX:vol
	C_SONG,          // SONG
	C_LOBBY,         // names
	C_START,         // null
	C_UPDATELOC,     // UUID:x:y
	C_KILLPLAYER,    // UUID
	C_SCORE,         // name:score
	C_SPAWNPLAYER,   // UUID:name:PlayerType
	C_SHOOT,         // UUID:focus
	C_SPAWNENEMY,    // UUID:EnemyType:x:y:scale
	C_SPAWNBOSS,     // UUID:BossType:x:y:scale
	C_KILLENEMY,     // UUID
	C_DAMAGEBOSS,    // UUID:phase
	C_DAMAGEPLAYER,  // UUID
	C_LEVELUP,       // UUID
	C_BOMB,          // UUID
	C_END,           // null
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
