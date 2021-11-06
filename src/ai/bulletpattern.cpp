#include "bulletpattern.h"
#include "bullettype.h"
#include "src/assets/texture.h"

namespace BulletPatterns {
const BulletList PLAYER_BASIC = BulletList()
																<< BulletInfo(Textures::PLAYERBULLETBASIC,
																							BulletType::PLAYERBASIC);

const BulletList FLOWERCIRCLE =
		BulletList() << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 30)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 60)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 90)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 120)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 150)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 180)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 210)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 240)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 270)
								 << BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 300)
								 << BulletInfo(Textures::BULLETELLIPSE,
															 BulletType::FLOWER,
															 330);

const BulletList SPRAY =
		BulletList()
		<< BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING)
		<< BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, 5)
		<< BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, 10)
		<< BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, -5)
		<< BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, -10)
		<< FLOWERCIRCLE;

BulletList operator<<(BulletList list, const BulletInfo& info) {
	list.push_back(info);
	return list;
}

BulletList operator<<(BulletList list, const BulletList& other) {
	foreach(BulletInfo info, other) { list.push_back(info); }
	return list;
}
}
