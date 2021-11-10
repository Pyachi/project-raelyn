#include "uuid.h"
#include "util.h"
#include <QStringList>

UUID::UUID()
		: UUID(static_cast<unsigned int>(Random::getInt()),
					 static_cast<unsigned int>(Random::getInt()),
					 static_cast<unsigned int>(Random::getInt()),
					 static_cast<unsigned int>(Random::getInt())) {}

UUID::UUID(const UUID& other)
		: UUID(other.sec1, other.sec2, other.sec3, other.sec4) {}

UUID::UUID(unsigned int sec1,
					 unsigned int sec2,
					 unsigned int sec3,
					 unsigned int sec4)
		: sec1(sec1), sec2(sec2), sec3(sec3), sec4(sec4) {}

QString UUID::toString() const {
	return QString::number(sec1) + "-" + QString::number(sec2) + "-" +
				 QString::number(sec3) + "-" + QString::number(sec4);
}

UUID UUID::fromString(const QString& string) {
	QStringList list = string.split('-');
	return UUID(list.at(0).toUInt(),
							list.at(1).toUInt(),
							list.at(2).toUInt(),
							list.at(3).toUInt());
}

bool UUID::operator==(const UUID& other) const {
	return (sec1 == other.sec1 && sec2 == other.sec2 && sec3 == other.sec3 &&
					sec4 == other.sec4);
}

bool UUID::operator<(const UUID& other) const {
	return (sec1 == other.sec1 ? sec2 == other.sec2
					? sec3 == other.sec3 ? sec4 < other.sec4 : sec3 < other.sec3
					: sec2 < other.sec2
					: sec1 < other.sec1);
}
