#include "boss.h"
#include "bullet.h"
#include "entityboss.h"
#include "entitybullet.h"
#include "entityplayer.h"
#include "game.h"
#include "uid.h"

Array<Ref<Boss> > Boss::list;

EntityBoss* Boss::spawn(const QPointF& loc, const UID& id, double scale) const {
	Array<int> scaledHealth = Array<int>(health.size());
	for (ushort i = 0; i < scaledHealth.size(); i++)
		scaledHealth[i] = static_cast<int>(health[i] * scale);
	EntityBoss* boss = new EntityBoss(tex, id, scaledHealth, ai);
  boss->setPos(loc);
  return boss;
}

const Boss Boss::LVL1MINI(Texture::ENEMY, {8000, 6000}, [](EntityBoss* boss) {
	switch (boss->phase) {
		case 0:
			if (boss->cycle(250, 10))
				boss->moveTo(
						{Random::getDouble(400) - 200, Random::getDouble(100) - 250},
						0,
						QUICK);
			if (boss->cycle(250, 100))
				boss->fireBullets(
						BulletInfo([](EntityBullet* bullet) { bullet->moveForward(2); },
											 Texture::ROUNDBLUE,
											 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10)
																	 << SpawnInfo(20) << SpawnInfo(-20)
																	 << SpawnInfo(30) << SpawnInfo(-30),
											 2)
								<< BulletInfo([](EntityBullet* bullet) {
																bullet->moveForward(2.5);
															},
															Texture::ROUNDBLUE,
															SpawnInfo(-5) << SpawnInfo(5) << SpawnInfo(15)
																						<< SpawnInfo(-15) << SpawnInfo(25)
																						<< SpawnInfo(-25),
															2)
								<< BulletInfo([](EntityBullet* bullet) {
																bullet->moveForward(3);
															},
															Texture::ROUNDBLUE,
															SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10)
																					<< SpawnInfo(20) << SpawnInfo(-20)
																					<< SpawnInfo(30) << SpawnInfo(-30),
															2)
								<< BulletInfo([](EntityBullet* bullet) {
																bullet->moveForward(3.5);
															},
															Texture::ROUNDBLUE,
															SpawnInfo(-5) << SpawnInfo(5) << SpawnInfo(15)
																						<< SpawnInfo(-15) << SpawnInfo(25)
																						<< SpawnInfo(-25),
															2)
								<< BulletInfo([](EntityBullet* bullet) {
																bullet->moveForward(4);
															},
															Texture::ROUNDBLUE,
															SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10)
																					<< SpawnInfo(20) << SpawnInfo(-20)
																					<< SpawnInfo(30) << SpawnInfo(-30),
															2)
								<< BulletInfo([](EntityBullet* bullet) {
																bullet->moveForward(5);
																bullet->rotate(0.2);
															},
															Texture::ELLIPSEAQUA,
															Pattern::CIRCLE16)
								<< BulletInfo([](EntityBullet* bullet) {
																bullet->moveForward(5);
																bullet->rotate(-0.2);
															},
															Texture::ELLIPSEAQUA,
															Pattern::CIRCLE16),
						boss->getDirectionOfEntity(Game::getPlayer()));
			break;
		case 1:
			if (boss->getAge() == 1)
				boss->moveTo({0, -200}, 0, QUICK);
			if (boss->getAge() > 120) {
				if (boss->cycle(10))
					boss->fireBullets(BulletInfo([](EntityBullet* bullet) {
																				 bullet->moveForward(2.5);
																				 bullet->rotate(0.25);
																			 },
																			 Texture::ELLIPSEAQUA,
																			 Pattern::CIRCLE12),
														boss->getAge());
				if (boss->cycle(120))
					boss->fireBullets(
							BulletInfo(
									Bullet::BASIC4, Texture::ROUNDBLUE, Pattern::CIRCLE16, 3),
							boss->getAge());
			}
			break;
	}
});
const Boss Boss::LVL1(Texture::ENEMY,
											{7500, 9000, 6000, 9000},
											[](EntityBoss* boss) {
	switch (boss->phase) {
		case 0:
			if (boss->getAge() == 1)
				boss->moveTo({0, -200}, 0, QUICK);
			if (boss->getAge() > 30 && boss->cycle(60))
				boss->fireBullets(
						BulletInfo(Bullet::BASIC5,
											 Texture::ROUNDRED,
											 (SpawnInfo(5) << SpawnInfo(15) << SpawnInfo(-5)
																		 << SpawnInfo(-15)) *
													 6,
											 2)
								<< BulletInfo(
											 Bullet::BASIC6,
											 Texture::ROUNDORANGE,
											 (SpawnInfo() << SpawnInfo(10) << SpawnInfo(-10)) * 6,
											 2) << BulletInfo(Bullet::BASIC7,
																				Texture::ROUNDYELLOW,
																				(SpawnInfo(5) << SpawnInfo(-5)) * 6,
																				2)
								<< BulletInfo(
											 Bullet::BASIC8, Texture::ROUNDYELLOW, SpawnInfo() * 6, 2)
								<< BulletInfo(Bullet::BASIC6,
															Texture::ELLIPSERED,
															(SpawnInfo() + 30) * 6,
															2) << BulletInfo(Bullet::BASIC7,
																							 Texture::ELLIPSEORANGE,
																							 (SpawnInfo() + 30) * 6,
																							 2)
								<< BulletInfo(Bullet::BASIC8,
															Texture::ELLIPSEYELLOW,
															(SpawnInfo() + 30) * 6,
															2),
						boss->getAge() / 2);
			break;
		case 1:
			if (boss->cycle(800, 1) || boss->cycle(800, 401))
				boss->moveTo({0, -200}, 0, QUICK);
			else if (boss->cycle(800, 201))
				boss->moveTo({-200, -200}, 0, QUICK);
			else if (boss->cycle(800, 601))
				boss->moveTo({200, -200}, 0, QUICK);
			else if (boss->cycle(200, 100))
				boss->fireBullets(BulletInfo(
						Bullet::FLOWER, Texture::ARROWYELLOW, SpawnInfo() * 24, 2));
			else if (boss->cycle(200, 110))
				boss->fireBullets(BulletInfo(
						Bullet::FLOWERREV, Texture::ARROWYELLOW, SpawnInfo() * 24, 2));
			else if (boss->cycle(200, 120))
				boss->fireBullets(BulletInfo(
						Bullet::FLOWER, Texture::ARROWORANGE, SpawnInfo() * 24, 2));
			else if (boss->cycle(200, 130))
				boss->fireBullets(BulletInfo(
						Bullet::FLOWERREV, Texture::ARROWORANGE, SpawnInfo() * 24, 2));
			else if (boss->cycle(200, 140))
				boss->fireBullets(
						BulletInfo(Bullet::FLOWER, Texture::ARROWRED, SpawnInfo() * 24, 2));
			else if (boss->cycle(200, 150))
				boss->fireBullets(BulletInfo(
						Bullet::FLOWERREV, Texture::ARROWRED, SpawnInfo() * 24, 2));
			break;
		case 2:
			if (boss->getAge() == 1)
				boss->moveTo({0, -200}, 0, QUICK);
			if (boss->cycle(90)) {
				List<SpawnInfo> list;
				int rand = Random::getInt(90) - 45;
				for (int i = 0; i < 170; i++) {
					list.push_back(SpawnInfo(rand));
					rand += 2;
				}
				boss->fireBullets(
						BulletInfo(Bullet::BASIC3, Texture::LAZERYELLOW, list, 2));
			}
			if (boss->cycle(90, 45))
				boss->fireBullets(BulletInfo(
						Bullet::BASIC3, Texture::ARROWYELLOW, Pattern::CIRCLE16, 2));
			break;
		case 3:
			if (boss->cycle(200, 10))
				boss->moveTo(
						{Random::getDouble(400) - 200, Random::getDouble(100) - 250},
						0,
						QUICK);
			if (boss->cycle(30))
				boss->fireBullets(BulletInfo(
						[](EntityBullet* bullet) {
							if (bullet->getAge() == 1)
								bullet->moveTo({Random::getDouble(500) - 250,
																Random::getDouble(100) - 250},
															 0,
															 QUICK);
							bullet->rotate(5);
							if (bullet->getAge() > 80 && bullet->getAge() < 120)
								bullet->fireBullets(BulletInfo(
										[](EntityBullet* bullet) { bullet->moveBy(0, 10); },
										Random::getInt(3) == 0
												? Texture::STARYELLOW
												: Random::getInt(2) == 0 ? Texture::ARROWORANGE
																								 : Texture::STARRED,
										SpawnInfo(0, {Random::getDouble(40) - 20, 0})));
							if (bullet->getAge() > 120)
								bullet->moveBy(0, bullet->getAge() - 120);
						},
						Texture::STARYELLOW,
						SpawnInfo(),
						3));
			break;
	}
});
const Boss Boss::LVL2MINI(Texture::ENEMY, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL2(Texture::ENEMY, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL3MINI(Texture::ENEMY, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL3(Texture::ENEMY, {50, 50}, [](EntityBoss*) {});
