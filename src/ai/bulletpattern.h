#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include "util.h"

enum Pattern {
	PATTERN_PLAYERBASIC,
	PATTERN_PLAYERBASICX2,
	PATTERN_PLAYERBASICX2C,
	PATTERN_PLAYERBASICX3,
	PATTERN_PLAYERBASICX3C,
	PATTERN_PLAYERBASICX5,
	PATTERN_PLAYERBASICX5C,
	PATTERN_PLAYERHOMINGX2,
	PATTERN_PLAYERHOMINGX2C,
	PATTERN_SHOTGUN8X3,
	PATTERN_SHOTGUN10X3,
	PATTERN_SHOTGUN12X3,
	PATTERN_SHOTGUN8X5,
	PATTERN_SHOTGUN10X5,
	PATTERN_SHOTGUN12X5,
	PATTERN_TRIPLESHOTGUNX3,
	PATTERN_TRIPLESHOTGUNX5
};

struct BulletInfo;

namespace Patterns {
extern List<BulletInfo> get(Pattern);
extern List<BulletInfo> operator<<(const BulletInfo&, const BulletInfo&);
extern List<BulletInfo> operator<<(Pattern, const BulletInfo&);
extern List<BulletInfo> operator<<(Pattern, Pattern);
extern List<BulletInfo> operator<<(List<BulletInfo>, Pattern);
extern List<BulletInfo> operator<<(List<BulletInfo>, const BulletInfo&);
extern List<BulletInfo> operator<<(List<BulletInfo>, const List<BulletInfo>&);
};  // namespace Patterns

#endif  // BULLETGROUP_H
