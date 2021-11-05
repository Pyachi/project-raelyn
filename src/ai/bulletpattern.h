#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include <QList>

class BulletInfo;

using BulletList = QList<BulletInfo*>;

class BulletPattern {
 public:
	static const BulletList PLAYER_BASIC;
	static const BulletList FLOWERCIRCLE;
	static const BulletList SPRAY;
};

#endif  // BULLETGROUP_H
