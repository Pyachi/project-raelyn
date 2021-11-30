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
		scaledHealth[i] = health[i] * scale;
	EntityBoss* boss = new EntityBoss(tex, id, scaledHealth, ai);
  boss->setPos(loc);
  return boss;
}

const Boss
		Boss::LVL1MINI(Texture::ENEMYTEMP, {8000, 6000}, [](EntityBoss* boss) {
			switch (boss->phase) {
				case 0:
					if (boss->cycle(250, 10))
						boss->moveTo(
								{Random::getDouble(400) - 200, Random::getDouble(100) - 250}, 0,
								QUICK);
					if (boss->cycle(250, 100))
						boss->fireBullets(
								BulletInfo([](EntityBullet* bullet) { bullet->moveForward(2); },
													 Texture::ROUNDBLUE,
													 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10)
																			 << SpawnInfo(20) << SpawnInfo(-20)
																			 << SpawnInfo(30) << SpawnInfo(-30),
													 2)
										<< BulletInfo(
													 [](EntityBullet* bullet) {
														 bullet->moveForward(2.5);
													 },
													 Texture::ROUNDBLUE,
													 SpawnInfo(-5) << SpawnInfo(5) << SpawnInfo(15)
																				 << SpawnInfo(-15) << SpawnInfo(25)
																				 << SpawnInfo(-25),
													 2)
										<< BulletInfo(
													 [](EntityBullet* bullet) { bullet->moveForward(3); },
													 Texture::ROUNDBLUE,
													 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10)
																			 << SpawnInfo(20) << SpawnInfo(-20)
																			 << SpawnInfo(30) << SpawnInfo(-30),
													 2)
										<< BulletInfo(
													 [](EntityBullet* bullet) {
														 bullet->moveForward(3.5);
													 },
													 Texture::ROUNDBLUE,
													 SpawnInfo(-5) << SpawnInfo(5) << SpawnInfo(15)
																				 << SpawnInfo(-15) << SpawnInfo(25)
																				 << SpawnInfo(-25),
													 2)
										<< BulletInfo(
													 [](EntityBullet* bullet) { bullet->moveForward(4); },
													 Texture::ROUNDBLUE,
													 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10)
																			 << SpawnInfo(20) << SpawnInfo(-20)
																			 << SpawnInfo(30) << SpawnInfo(-30),
													 2)
										<< BulletInfo(
													 [](EntityBullet* bullet) {
														 bullet->moveForward(5);
														 bullet->rotate(0.2);
													 },
													 Texture::ELLIPSEAQUA, Pattern::CIRCLE16)
										<< BulletInfo(
													 [](EntityBullet* bullet) {
														 bullet->moveForward(5);
														 bullet->rotate(-0.2);
													 },
													 Texture::ELLIPSEAQUA, Pattern::CIRCLE16),
								boss->getDirectionOfEntity(Game::getPlayer()));
					break;
				case 1:
					if (boss->getAge() == 1)
						boss->moveTo({0, -200}, 0, QUICK);
					if (boss->getAge() > 120) {
						if (boss->cycle(10))
							boss->fireBullets(BulletInfo(
																		[](EntityBullet* bullet) {
																			bullet->moveForward(2.5);
																			bullet->rotate(0.25);
																		},
																		Texture::ELLIPSEAQUA, Pattern::CIRCLE12),
																boss->getAge());
						if (boss->cycle(120))
							boss->fireBullets(BulletInfo(Bullet::BASIC4, Texture::ROUNDBLUE,
																					 Pattern::CIRCLE16, 3),
																boss->getAge());
					}
					break;
			}
		});
const Boss Boss::LVL1(Texture::ENEMYTEMP,
											{6000, 4000, 2000, 6000, 8000},
											[](EntityBoss* boss) {
												switch (boss->phase) {
													case 0:
														if (boss->getAge() == 1)
															boss->moveTo({0, -200}, 0, QUICK);
														break;
													case 1:
														break;
													case 2:
														break;
													case 3:
														break;
													case 4:
														break;
												}
											});
const Boss Boss::LVL2MINI(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss* boss) {
});
const Boss Boss::LVL2(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss* boss) {});
const Boss Boss::LVL3MINI(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss* boss) {
});
const Boss Boss::LVL3(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss* boss) {});
