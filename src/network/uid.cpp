#include "uid.h"

UID::UID(void)
		: UID(static_cast<unsigned int>(Random::getInt()),
					static_cast<unsigned int>(Random::getInt()),
					static_cast<unsigned int>(Random::getInt()),
					static_cast<unsigned int>(Random::getInt())) {}

UID::UID(const UID& other)
		: UID(other.sec1, other.sec2, other.sec3, other.sec4) {}

UID::UID(unsigned int sec1,
				 unsigned int sec2,
				 unsigned int sec3,
				 unsigned int sec4)
		: sec1(sec1), sec2(sec2), sec3(sec3), sec4(sec4) {}

QString UID::toString(void) const {
	return QString::number(sec1) + "-" + QString::number(sec2) + "-" +
				 QString::number(sec3) + "-" + QString::number(sec4);
}

UID UID::fromString(const QString& string) {
	QStringList list = string.split('-');
	return UID(list.at(0).toUInt(),
						 list.at(1).toUInt(),
						 list.at(2).toUInt(),
						 list.at(3).toUInt());
}

bool UID::operator==(const UID& other) const {
	return (sec1 == other.sec1 && sec2 == other.sec2 && sec3 == other.sec3 &&
					sec4 == other.sec4);
}

bool UID::operator<(const UID& other) const {
	return (sec1 == other.sec1 ? sec2 == other.sec2
					? sec3 == other.sec3 ? sec4 < other.sec4 : sec3 < other.sec3
					: sec2 < other.sec2
					: sec1 < other.sec1);
}
