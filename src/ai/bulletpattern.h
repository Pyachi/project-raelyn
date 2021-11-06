#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include "bullettype.h"

using BulletList = std::vector<BulletInfo>;

namespace BulletPatterns {
extern const BulletList PLAYER_BASIC;
extern const BulletList FLOWERCIRCLE;
extern const BulletList SPRAY;

extern BulletList operator<<(BulletList, const BulletInfo&);
extern BulletList operator<<(BulletList, const BulletList&);
};

#endif  // BULLETGROUP_H
