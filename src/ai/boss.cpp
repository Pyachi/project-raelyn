#include "boss.h"
#include "bullet.h"
#include "entityboss.h"
#include "entitybullet.h"
#include "entityplayer.h"
#include "game.h"
#include "uid.h"

Array<Ref<Boss> > Boss::list;

EntityBoss* Boss::spawn(const QPointF& loc, const UID& id) const {
  EntityBoss* boss = new EntityBoss(tex, id, health, ai);
  boss->setPos(loc);
  return boss;
}

const Boss
		Boss::LVL1MINI(Texture::ENEMYTEMP, {4000, 2500}, [](EntityBoss* boss) {
			switch (boss->phase) {
				case 0:
					if (boss->cycle(1000, 10) || boss->cycle(1000, 510))
						boss->moveTo({0, -200}, 100, QUICK);
					if (boss->cycle(1000, 260))
						boss->moveTo({-200, -200}, 100, QUICK);
					if (boss->cycle(1000, 760))
						boss->moveTo({200, -200}, 100, QUICK);
					if (boss->cycle(250, 100) || boss->cycle(250, 150) ||
							boss->cycle(250, 200))
						boss->fireBullets(
								BulletInfo(Bullet::BASIC4, Texture::ROUNDBLUE,
													 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10), 2)
										<< BulletInfo(Bullet::BASIC5, Texture::ROUNDBLUE,
																	SpawnInfo(-5) << SpawnInfo(5), 2)
										<< BulletInfo(
													 Bullet::BASIC6, Texture::ROUNDBLUE,
													 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10), 2)
										<< BulletInfo(Bullet::BASIC7, Texture::ROUNDBLUE,
																	SpawnInfo(-5) << SpawnInfo(5), 2)
										<< BulletInfo(
													 Bullet::BASIC8, Texture::ROUNDBLUE,
													 SpawnInfo() << SpawnInfo(-10) << SpawnInfo(10), 2),
								boss->getDirectionOfEntity(Game::getPlayer()));
					if (boss->cycle(250, 100))
						boss->fireBullets(BulletInfo(
																	[](EntityBullet* bullet) {
																		bullet->moveForward(3);
																		bullet->rotate(0.5);
																	},
																	Texture::ELLIPSEAQUA, Pattern::CIRCLE16)
															<< BulletInfo(
																		 [](EntityBullet* bullet) {
																			 bullet->moveForward(3);
																			 bullet->rotate(-0.5);
																		 },
																		 Texture::ELLIPSEAQUA, Pattern::CIRCLE16));
					break;
				case 1:
					if (boss->getAge() == 1)
						boss->moveTo({0, -200}, 0, QUICK);
					if (boss->getAge() > 120) {
						if (boss->cycle(10))
							boss->fireBullets(BulletInfo(
																		[](EntityBullet* bullet) {
																			bullet->moveForward(5);
																			bullet->rotate(0.5);
																		},
																		Texture::ELLIPSEAQUA, Pattern::CIRCLE12),
																boss->getAge());
						if (boss->cycle(120))
							boss->fireBullets(BulletInfo(Bullet::BASIC8, Texture::ROUNDBLUE,
																					 Pattern::CIRCLE16, 3),
																boss->getAge());
					}
					break;
			}
		});
const Boss Boss::LVL1(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL2MINI(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL2(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL3MINI(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss*) {});
const Boss Boss::LVL3(Texture::ENEMYTEMP, {50, 50}, [](EntityBoss*) {});
