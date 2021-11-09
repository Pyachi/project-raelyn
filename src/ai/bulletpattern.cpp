#include "bulletpattern.h"
#include "bullet.h"
#include "src/assets/texture.h"

namespace BulletPatterns {
const List<BulletInfo> PLAYER_BASIC =
		List<BulletInfo>() << BulletInfo{TEXPLAYERBULLET, PLAYERBASIC};

const List<BulletInfo> PLAYER_HOMING =
		List<BulletInfo>() << BulletInfo{TEXPLAYERBULLET, PLAYERHOMING, 0,
																		 QPointF(50, -20)}
											 << BulletInfo{TEXPLAYERBULLET, PLAYERHOMING, 0,
																		 QPointF(-50, -20)};

const List<BulletInfo> FLOWERCIRCLE =
		List<BulletInfo>() << BulletInfo{TEXBULLETELLIPSE, FLOWER}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 30}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 60}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 90}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 120}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 150}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 180}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 210}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 240}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 270}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 300}
											 << BulletInfo{TEXBULLETELLIPSE, FLOWER, 330};

const List<BulletInfo> SPRAY = List<BulletInfo>()
															 << BulletInfo{TEXBULLETROUND, ACCELERATING}
															 << BulletInfo{TEXBULLETROUND, ACCELERATING, 5}
															 << BulletInfo{TEXBULLETROUND, ACCELERATING, 10}
															 << BulletInfo{TEXBULLETROUND, ACCELERATING, -5}
															 << BulletInfo{TEXBULLETROUND, ACCELERATING, -10}
															 << FLOWERCIRCLE;

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
}  // namespace BulletPatterns
