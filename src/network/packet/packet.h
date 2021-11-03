#ifndef BASEPACKET_H
#define BASEPACKET_H

#include <QString>

class Packet {
 public:
	Packet();
	virtual ~Packet();

	virtual QString encode() const = 0;
};

#endif  // BASEPACKET_H
