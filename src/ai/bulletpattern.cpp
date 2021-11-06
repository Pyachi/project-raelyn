#include "bulletpattern.h"
#include "bullettype.h"
#include "bulletinfo.h"
#include "src/assets/texture.h"

const BulletList BulletPattern::PLAYER_BASIC =
		BulletList() << new BulletInfo(Textures::PLAYERBULLETBASIC,
																	 BulletType::PLAYERBASIC);

const BulletList BulletPattern::FLOWERCIRCLE =
		BulletList()
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 30)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 60)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 90)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 120)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 150)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 180)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 210)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 240)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 270)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 300)
		<< new BulletInfo(Textures::BULLETELLIPSE, BulletType::FLOWER, 330);

const BulletList BulletPattern::SPRAY =
		BulletList()
		<< new BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING)
		<< new BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, 5)
		<< new BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, 10)
		<< new BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, -5)
		<< new BulletInfo(Textures::BULLETROUND, BulletType::ACCELERATING, -10)
		<< FLOWERCIRCLE;
