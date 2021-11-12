#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include "util.h"

enum Pattern {
	PATTERN_CIRCLE4,
	PATTERN_CIRCLE8,
	PATTERN_CIRCLE16,
	PATTERN_SHOTGUNX3,
	PATTERN_SHOTGUNX5,
};

struct BulletInfo {
	BulletInfo(double rot = 0, const QPointF& loc = {0, 0}, int scale = 1);
	double rot;
	QPointF loc;
	int scale;
};

namespace Patterns {
extern List<BulletInfo> get(Pattern pat);
};  // namespace Patterns

extern List<BulletInfo> operator<<(const BulletInfo& info1,
																	 const BulletInfo& info2);
extern List<BulletInfo> operator<<(Pattern pat, const BulletInfo& info);
extern List<BulletInfo> operator<<(Pattern pat1, Pattern pat2);
extern List<BulletInfo> operator<<(List<BulletInfo> list, Pattern pat);
extern List<BulletInfo> operator<<(List<BulletInfo> list,
																	 const BulletInfo& info);
extern List<BulletInfo> operator<<(List<BulletInfo> list1,
																	 const List<BulletInfo>& list2);

#endif  // BULLETGROUP_H
