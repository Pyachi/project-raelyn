#include "bulletpattern.h"
#include "assets.h"
#include "bullettype.h"
#include "bulletinfo.h"

const BulletList BulletPattern::PLAYER_BASIC =
		BulletList() << new BulletInfo(Texture::PLAYERBULLETBASIC,
																	 BulletType::PLAYERBASIC);

const BulletList BulletPattern::FLOWERCIRCLE =
		BulletList()
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 30)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 60)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 90)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 120)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 150)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 180)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 210)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 240)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 270)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 300)
		<< new BulletInfo(Texture::BULLETELLIPSE, BulletType::FLOWER, 330);

const BulletList BulletPattern::SPRAY =
		BulletList()
		<< new BulletInfo(Texture::BULLETROUND, BulletType::ACCELERATING)
		<< new BulletInfo(Texture::BULLETROUND, BulletType::ACCELERATING, 5)
		<< new BulletInfo(Texture::BULLETROUND, BulletType::ACCELERATING, 10)
		<< new BulletInfo(Texture::BULLETROUND, BulletType::ACCELERATING, -5)
		<< new BulletInfo(Texture::BULLETROUND, BulletType::ACCELERATING, -10)
		<< FLOWERCIRCLE;
