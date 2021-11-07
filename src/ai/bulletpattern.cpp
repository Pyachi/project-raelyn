#include "bulletpattern.h"
#include "src/assets/texture.h"
#include "bulletai.h"

namespace BulletPatterns {
const List<BulletInfo> PLAYER_BASIC = List<BulletInfo>()
																			<< BulletInfo{Textures::PLAYERBULLETBASIC,
																										BulletType::PLAYERBASIC};

const List<BulletInfo> PLAYER_HOMING =
		List<BulletInfo>()
		<< BulletInfo{Textures::PLAYERBULLETBASIC, BulletType::PLAYERHOMING,
									0,                           QPointF(50, -20)}
		<< BulletInfo{Textures::PLAYERBULLETBASIC, BulletType::PLAYERHOMING,
									0,                           QPointF(-50, -20)};

const List<BulletInfo> FLOWERCIRCLE =
		List<BulletInfo>()
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 30}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 60}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 90}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 120}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 150}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 180}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 210}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 240}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 270}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 300}
		<< BulletInfo{Textures::BULLETELLIPSE, BulletType::FLOWER, 330};

const List<BulletInfo> SPRAY =
		List<BulletInfo>()
		<< BulletInfo{Textures::BULLETROUND, BulletType::ACCELERATING}
		<< BulletInfo{Textures::BULLETROUND, BulletType::ACCELERATING, 5}
		<< BulletInfo{Textures::BULLETROUND, BulletType::ACCELERATING, 10}
		<< BulletInfo{Textures::BULLETROUND, BulletType::ACCELERATING, -5}
		<< BulletInfo{Textures::BULLETROUND, BulletType::ACCELERATING, -10}
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
}
