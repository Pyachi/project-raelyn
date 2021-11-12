#include "pattern.h"
#include "AI"

namespace Patterns {
List<BulletInfo> get(Pattern pattern) {
	// BulletInfo{AI, ROTATION, POSITION, DAMAGE};
	switch (pattern) {
		case PATTERN_CIRCLE4:
			return BulletInfo() << BulletInfo(90) << BulletInfo(180)
													<< BulletInfo(270);
		case PATTERN_CIRCLE8:
			return BulletInfo(45) << BulletInfo(135) << BulletInfo(225)
														<< BulletInfo(315) << PATTERN_CIRCLE4;
		case PATTERN_CIRCLE16:
			return BulletInfo(22.5) << BulletInfo(67.5) << BulletInfo(112.5)
															<< BulletInfo(157.5) << BulletInfo(202.5)
															<< BulletInfo(247.5) << BulletInfo(292.5)
															<< BulletInfo(337.5) << PATTERN_CIRCLE8;
		case PATTERN_SHOTGUNX3:
			return BulletInfo() << BulletInfo(-20) << BulletInfo(20);
		case PATTERN_SHOTGUNX5:
			return BulletInfo(40) << BulletInfo(-40) << PATTERN_SHOTGUNX3;
	}
}
}  // namespace Patterns

BulletInfo::BulletInfo(double rot, const QPointF& loc, int scale)
		: rot(rot), loc(loc), scale(scale) {}

List<BulletInfo> operator<<(const BulletInfo& info1, const BulletInfo& info2) {
	return List<BulletInfo>() << info1 << info2;
}

List<BulletInfo> operator<<(Pattern pattern, const BulletInfo& info) {
	return Patterns::get(pattern) << info;
}

List<BulletInfo> operator<<(Pattern pattern1, Pattern pattern2) {
	return Patterns::get(pattern1) << Patterns::get(pattern2);
}

List<BulletInfo> operator<<(List<BulletInfo> list, Pattern pattern) {
	return list << Patterns::get(pattern);
}

List<BulletInfo> operator<<(List<BulletInfo> list, const BulletInfo& info) {
	list.emplace_back(info);
	return list;
}

List<BulletInfo> operator<<(List<BulletInfo> list,
														const List<BulletInfo>& other) {
	for (BulletInfo info : other) {
		list.emplace_back(info);
	}
	return list;
}
