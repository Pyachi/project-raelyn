#ifndef UID_H
#define UID_H

#include <QString>

class UID {
 public:
	UID(void);
	UID(const UID&);

	QString toString(void) const;
	static UID fromString(const QString&);

	bool operator==(const UID&) const;
	bool operator<(const UID&) const;

 private:
	UID(unsigned int, unsigned int, unsigned int, unsigned int);

	unsigned int sec1;
	unsigned int sec2;
	unsigned int sec3;
	unsigned int sec4;
};

#endif  // UID_H
