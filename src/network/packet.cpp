#include "packet.h"

Packet::Packet(const Header& header, const QStringList& data)
		: header(header), data(data) {}

QByteArray Packet::encode() const {
	QByteArray packet = QByteArray::number(header);
	foreach(QString segment, data) {
		packet += ':';
		packet += segment;
	}
	packet += ';';
	return packet;
}

QList<Packet> Packet::decode(const QByteArray& fullPacket) {
	QList<Packet> list;
	foreach(QByteArray packet, fullPacket.split(';')) {
		if (packet.isEmpty())
			continue;
		QList<QByteArray> segments = packet.split(':');
		Header header = static_cast<Header>(segments.takeFirst().toInt());
		QStringList data;
		foreach(QByteArray segment, segments) { data.append(segment); }
		list.append(Packet(header, data));
	}
	return list;
}