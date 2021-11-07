#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include "alias.h"

class BulletInfo;

namespace BulletPatterns {
extern const List<BulletInfo> PLAYER_BASIC;
extern const List<BulletInfo> PLAYER_HOMING;
extern const List<BulletInfo> FLOWERCIRCLE;
extern const List<BulletInfo> SPRAY;

extern List<BulletInfo> operator<<(List<BulletInfo>, const BulletInfo&);
extern List<BulletInfo> operator<<(List<BulletInfo>, const List<BulletInfo>&);
};  // namespace BulletPatterns

#endif  // BULLETGROUP_H
