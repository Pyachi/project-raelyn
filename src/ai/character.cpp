#include "character.h"
#include "entitybomb.h"
#include "entitybullet.h"
#include "entityplayer.h"
#include "game.h"
#include "sfx.h"
#include "texture.h"

Array<Ref<Character> > Character::list;

//***************************************************************************
//***************************************************************************
//***************************************************************************
const Character Character::PYACHI(
    "Character: Pyachi",
    Texture::PYACHI,
		8,
    3,
		[](EntityPlayer* player) -> const List<BulletInfo> {
      List<BulletInfo> list;
			SFX::FIRE1.play(3);
      switch (player->level) {
					//***************************************************************************
					/* PYACHI Level 4:
					 * Basic: 60 * 4 * 3 = 720
					 * Homing: 4 * 40 = 160
					 * Trail: 4 * 5 * 2 = 40
					 * Explosion: 4 * 16 * 1 = 64
					 * Total: 984
					 */
        case 4:
					if (!player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEORANGE,
																			SpawnInfo(5, {15, -13})
																					<< SpawnInfo(-5, {-15, -13})
																					<< SpawnInfo(15, {0, -13})
																					<< SpawnInfo(-15, {0, -13}),
																			1, 3));
					else
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEORANGE,
																			SpawnInfo(0, {20, -13})
																					<< SpawnInfo(0, {-20, -13})
																					<< SpawnInfo(0, {10, -13})
																					<< SpawnInfo(0, {-10, -13}),
																			1, 3));
					if (player->cycle(15))
						list.push_back(BulletInfo(
								[](EntityBullet* bullet) {
									double dir = bullet->getDirectionOfEntity(
											bullet->getNearestEntity(ENEMY));
									dir -= bullet->rotation();
									if (dir == 180 || dir == -180)
										dir = 0;
									while (dir > 180)
										dir -= 360;
									while (dir < -180)
										dir += 360;
									dir = dir > 10 ? 10 : dir < -10 ? -10 : dir;
									bullet->rotate(dir);
									bullet->moveForward(20);
									if (bullet->getCollisions(ENEMY).size() != 0)
										bullet->fireBullets(
												BulletInfo(
														[](EntityBullet* bullet) {
															if (bullet->getAge() == 1)
																bullet->borderCheck = false;
															if (bullet->getAge() == 10)
																bullet->collisionCheck = true;
															bullet->moveForward(20);
															bullet->rotate(18);
															if (bullet->getAge() == 20)
																bullet->deleteLater();
														},
														Texture::ELLIPSEYELLOW, Pattern::CIRCLE16, 1, 1),
												0, {0, 0}, false);
								},
								Texture::ELLIPSERED, SpawnInfo(0, {0, -13}), 2, 40));
					if (player->cycle(15, 1, 5))
						list.push_back(BulletInfo(
								[](EntityBullet* bullet) {
									double dir = bullet->getDirectionOfEntity(
											bullet->getNearestEntity(ENEMY));
									dir -= bullet->rotation();
									if (dir == 180 || dir == -180)
										dir = 0;
									while (dir > 180)
										dir -= 360;
									while (dir < -180)
										dir += 360;
									dir = dir > 10 ? 10 : dir < -10 ? -10 : dir;
									bullet->rotate(dir);
									bullet->moveForward(20);
								},
								Texture::ELLIPSEORANGE, SpawnInfo(0, {0, -13}), 1, 2));
					break;
					//***************************************************************************
					/* PYACHI Level 3:
					 * Basic: 60 * 4 * 3 = 720
					 * Homing: 4 * 40 = 160
					 * Total: 880
					 */
        case 3:
					if (!player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
																			SpawnInfo(5, {15, -13})
																					<< SpawnInfo(-5, {-15, -13})
																					<< SpawnInfo(15, {0, -13})
																					<< SpawnInfo(-15, {0, -13}),
																			1, 3));
					else
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
																			SpawnInfo(0, {20, -13})
																					<< SpawnInfo(0, {-20, -13})
																					<< SpawnInfo(0, {10, -13})
																					<< SpawnInfo(0, {-10, -13}),
																			1, 3));
					if (player->cycle(15))
						list.push_back(BulletInfo(
								[](EntityBullet* bullet) {
									double dir = bullet->getDirectionOfEntity(
											bullet->getNearestEntity(ENEMY));
									dir -= bullet->rotation();
									if (dir == 180 || dir == -180)
										dir = 0;
									while (dir > 180)
										dir -= 360;
									while (dir < -180)
										dir += 360;
									dir = dir > 8 ? 8 : dir < -8 ? -8 : dir;
									bullet->rotate(dir);
									bullet->moveForward(20);
								},
								Texture::ELLIPSEYELLOW, SpawnInfo(0, {0, -13}), 2, 40));
					break;
					//***************************************************************************
					/* PYACHI Level 2:
					 * Basic: 60 * 3 * 3 = 540
					 * Homing: 4 * 50 = 200
					 * Total: 740
					 */
        case 2:
					if (!player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
																			SpawnInfo(5, {15, -13})
																					<< SpawnInfo(-5, {-15, -13})
																					<< SpawnInfo(0, {0, -13}),
																			1, 3));
					else
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
																			SpawnInfo(0, {15, -13})
																					<< SpawnInfo(0, {-15, -13})
																					<< SpawnInfo(0, {0, -13}),
																			1, 3));
					if (player->cycle(15))
						list.push_back(BulletInfo(
								[](EntityBullet* bullet) {
									double dir = bullet->getDirectionOfEntity(
											bullet->getNearestEntity(ENEMY));
									dir -= bullet->rotation();
									if (dir == 180 || dir == -180)
										dir = 0;
									while (dir > 180)
										dir -= 360;
									while (dir < -180)
										dir += 360;
									dir = dir > 5 ? 5 : dir < -5 ? -5 : dir;
									bullet->rotate(dir);
									bullet->moveForward(20);
								},
								Texture::ELLIPSEYELLOW, SpawnInfo(0, {0, -13}), 2, 50));
          break;
					//***************************************************************************
					/* PYACHI Level 1:
					 * Basic: 60 * 2 * 4 = 480
					 * Homing: 4 * 40 = 160
					 * Total: 640
					 */
        case 1:
        default:
					if (!player->focus)
						list.push_back(BulletInfo(
								Bullet::BASIC40, Texture::ELLIPSEYELLOW,
								SpawnInfo(5, {15, -13}) << SpawnInfo(-5, {-15, -13}), 1, 4));
					else
						list.push_back(BulletInfo(
								Bullet::BASIC40, Texture::ELLIPSEYELLOW,
								SpawnInfo(0, {15, -13}) << SpawnInfo(0, {-15, -13}), 1, 4));
					if (player->cycle(15))
						list.push_back(BulletInfo(
								[](EntityBullet* bullet) {
									double dir = bullet->getDirectionOfEntity(
											bullet->getNearestEntity(ENEMY));
									dir -= bullet->rotation();
									if (dir == 180 || dir == -180)
										dir = 0;
									while (dir > 180)
										dir -= 360;
									while (dir < -180)
										dir += 360;
									dir = dir > 2 ? 2 : dir < -2 ? -2 : dir;
									bullet->rotate(dir);
									bullet->moveForward(20);
								},
								Texture::ELLIPSEYELLOW, SpawnInfo(0, {0, -13}), 2, 40));
					//***************************************************************************
      }
      return list;
		},
		[](EntityPlayer*) -> BombInfo {
			return BombInfo(
					[](EntityBomb* bullet) {
						double dir = 0;
						if (bullet->getNearestEntity(ENEMY) == nullptr) {
							if (bullet->getNearestEntity(BULLET) != nullptr) {
								EntityBullet* other = dynamic_cast<EntityBullet*>(
										bullet->getNearestEntity(BULLET));
								if (other->ownerType == ENEMY)
									dir = bullet->getDirectionOfEntity(other);
								else
									dir = bullet->getDirectionOfEntity(Game::getPlayer());
							} else
								dir = bullet->getDirectionOfEntity(Game::getPlayer());
						} else
							dir =
									bullet->getDirectionOfEntity(bullet->getNearestEntity(ENEMY));
						dir -= bullet->rotation();
						if (dir == 180 || dir == -180)
							dir = 0;
						while (dir > 180)
							dir -= 360;
						while (dir < -180)
							dir += 360;
						dir = dir > 30 ? 30 : dir < -30 ? -30 : dir;
						bullet->rotate(dir);
						bullet->moveForward(40);
						if (bullet->getAge() == 300) {
							bullet->fireBullets(
									BulletInfo(Bullet::BASIC10, Texture::ELLIPSEYELLOW,
														 Pattern::CIRCLE32, 2, 50)
									<< BulletInfo(Bullet::BASIC7, Texture::ELLIPSEORANGE,
																Pattern::CIRCLE32, 2, 50)
									<< BulletInfo(Bullet::BASIC4, Texture::ELLIPSERED,
																Pattern::CIRCLE32, 2, 50));
							bullet->deleteLater();
						}
					},
					Texture::ELLIPSERED, 5, 500);
		});
//***************************************************************************
//***************************************************************************
//***************************************************************************
const Character Character::AERON(
    "Character: Aeron",
    Texture::AERON,
    12,
    5,
		[](EntityPlayer* player) -> const List<BulletInfo> {
      List<BulletInfo> list;

      switch (player->level) {
        case 4:
          if (player->focus) {
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWBLUE,
																			SpawnInfo(5, {-40, -13})
																					<< SpawnInfo(-5, {40, -13})));
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWAQUA,
																			SpawnInfo(0, {0, -13})));
          } else {
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWBLUE,
																			SpawnInfo(10, {-40, -13})
																					<< SpawnInfo(-10, {40, -13})));
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWAQUA,
																			SpawnInfo(0, {0, -13})));
          }
          break;
        case 3:
          if (player->focus) {
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWBLUE,
																			SpawnInfo(5, {-40, -13})
																					<< SpawnInfo(-5, {40, -13})));
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWAQUA,
																			SpawnInfo(0, {0, -13})));
          } else {
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWBLUE,
																			SpawnInfo(10, {-40, -13})
																					<< SpawnInfo(-10, {40, -13})));
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWAQUA,
																			SpawnInfo(0, {0, -13})));
          }
          break;
        case 2:
          if (player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWBLUE,
																			SpawnInfo(5, {-40, -13})
																					<< SpawnInfo(-5, {40, -13})));
          else
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWBLUE,
																			SpawnInfo(10, {-40, -13})
																					<< SpawnInfo(-10, {40, -13})));
          break;
        case 1:

        default:
					list.push_back(BulletInfo(Bullet::BASIC40, Texture::ARROWAQUA,
																		SpawnInfo(0, {0, -13})));
      }
      return list;
    },
		[](EntityPlayer*) -> const BombInfo {
			return BombInfo([](EntityBomb*) {}, Texture::BOMB);
		});
//***************************************************************************
//***************************************************************************
//***************************************************************************
const Character Character::PRYSMA(
		"Character: Prysma",
		Texture::PRYSMA,
		15,
		8,
		[](EntityPlayer*) -> const List<BulletInfo> { return List<BulletInfo>(); },
		[](EntityPlayer*) -> const BombInfo {
			return BombInfo([](EntityBomb*) {}, Texture::BOMB);
		});
//***************************************************************************
//***************************************************************************
//***************************************************************************
const Character Character::ANEKHANDA(
		"Character: Anekhanda",
		Texture::ANEKHANDA,
		8,
		6,
		[](EntityPlayer*) -> const List<BulletInfo> { return List<BulletInfo>(); },
		[](EntityPlayer*) -> const BombInfo {
			return BombInfo([](EntityBomb*) {}, Texture::BOMB);
		});
