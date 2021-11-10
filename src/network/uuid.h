#ifndef UUID_H
#define UUID_H

#include <QString>

class UUID {
 public:
	UUID(void);
	UUID(const UUID&);

	QString toString(void) const;
	static UUID fromString(const QString&);

	bool operator==(const UUID&) const;
	bool operator<(const UUID&) const;

 private:
	UUID(unsigned int, unsigned int, unsigned int, unsigned int);

	unsigned int sec1;
	unsigned int sec2;
	unsigned int sec3;
	unsigned int sec4;
};

#endif  // UUID_H
