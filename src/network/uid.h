#ifndef UID_H
#define UID_H

#include "util.h"

class UID {
 public:
	UID(void);
	UID(const UID& id);

	QString toString(void) const;
	static UID fromString(const QString& string);

	bool operator==(const UID& id) const;
	bool operator<(const UID& id) const;

 private:
	UID(unsigned int, unsigned int, unsigned int, unsigned int);

	unsigned int sec1;
	unsigned int sec2;
	unsigned int sec3;
	unsigned int sec4;
};

#endif  // UID_H
