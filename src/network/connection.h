#ifndef CONNECTION_H
#define CONNECTION_H

template <class T>
class Packet;

class Connection {
 public:
		template <class T>
		static void sendPacket(Packet<T>);




	Connection();
};

#endif  // CONNECTION_H
