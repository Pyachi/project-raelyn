#include "character.h"
#include "entityplayer.h"
#include "sfx.h"
#include "texture.h"
#include "entitybullet.h"

Array<Ref<Character> > Character::list;

// FOR ANEKHANDA BOMB :)
/*
double dir = bullet->getDirectionOfEntity(
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																bullet->getNearestEntity(ENEMY));
dir -= bullet->rotation();
while (dir > 180)
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																dir -= 360;
while (dir < -180)
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																dir += 360;
dir = dir > 5 ? 5 : dir < -5 ? -5 : dir;
bullet->rotate(dir);
double dis = 20.0 / dir;
if (dis < 0)
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																dis *= -1;
if (dis > 30)
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																dis = 30;
bullet->moveForward(dis);
*/

const Character Character::PYACHI(
		"Character: Pyachi",
    Texture::PYACHI,
    10,
    3,
		[](EntityPlayer* player)->const List<BulletInfo> {
      List<BulletInfo> list;

      switch (player->level) {
        case 4:

        case 3:

        case 2:
          if (player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ELLIPSEYELLOW,
                                      SpawnInfo(0, {10, -13})
                                          << SpawnInfo(0, {-10, -13})));
          else
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ELLIPSEYELLOW,
                                      SpawnInfo(10, {10, -13})
                                          << SpawnInfo(-10, {-10, -13})));
					break;
        case 1:
        default:
					if (!player->focus) {
						list.push_back(
								BulletInfo(Bullet::BASIC40,
													 Texture::ELLIPSEYELLOW,
													 SpawnInfo(0, {15, -13}) << SpawnInfo(0, {-15, -13}),
													 1,
													 5));
					} else {
						if (player->cycle(15))
							list.push_back(
									BulletInfo([](EntityBullet* bullet) {
															 double dir = bullet->getDirectionOfEntity(
																	 bullet->getNearestEntity(ENEMY));
															 dir -= bullet->rotation();
															 while (dir > 180)
																 dir -= 360;
															 while (dir < -180)
																 dir += 360;
															 dir = dir > 5 ? 5 : dir < -5 ? -5 : dir;
															 bullet->rotate(dir);
															 bullet->moveForward(40);
														 },
														 Texture::ELLIPSEYELLOW,
														 SpawnInfo(0, {0, -13}),
														 2,
														 100));
						list.push_back(
								BulletInfo(Bullet::BASIC40,
													 Texture::ELLIPSEYELLOW,
													 SpawnInfo(0, {5, -13}) << SpawnInfo(0, {-5, -13}),
													 1,
													 2));
					}
      }
      return list;
    },
		[](EntityPlayer* player)->const SFX& {
      switch (player->level) {
        default:
        case 1:
          return SFX::FIRE1;
        case 2:
          return SFX::FIRE1;
        case 3:
          return SFX::FIRE1;
        case 4:
          return SFX::FIRE1;
      }
    });

const Character Character::AERON(
		"Character: Aeron",
    Texture::AERON,
    12,
    5,
		[](EntityPlayer* player)->const List<BulletInfo> {
      List<BulletInfo> list;

      switch (player->level) {
        case 4:
          if (player->focus) {
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ARROWBLUE,
                                      SpawnInfo(5, {-40, -13})
                                          << SpawnInfo(-5, {40, -13})));
						list.push_back(BulletInfo(
								Bullet::BASIC40, Texture::ARROWAQUA, SpawnInfo(0, {0, -13})));
          } else {
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ARROWBLUE,
                                      SpawnInfo(10, {-40, -13})
                                          << SpawnInfo(-10, {40, -13})));
						list.push_back(BulletInfo(
								Bullet::BASIC40, Texture::ARROWAQUA, SpawnInfo(0, {0, -13})));
          }
          break;
        case 3:
          if (player->focus) {
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ARROWBLUE,
                                      SpawnInfo(5, {-40, -13})
                                          << SpawnInfo(-5, {40, -13})));
						list.push_back(BulletInfo(
								Bullet::BASIC40, Texture::ARROWAQUA, SpawnInfo(0, {0, -13})));
          } else {
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ARROWBLUE,
                                      SpawnInfo(10, {-40, -13})
                                          << SpawnInfo(-10, {40, -13})));
						list.push_back(BulletInfo(
								Bullet::BASIC40, Texture::ARROWAQUA, SpawnInfo(0, {0, -13})));
          }
          break;
        case 2:
          if (player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ARROWBLUE,
                                      SpawnInfo(5, {-40, -13})
                                          << SpawnInfo(-5, {40, -13})));
          else
						list.push_back(BulletInfo(Bullet::BASIC40,
																			Texture::ARROWBLUE,
                                      SpawnInfo(10, {-40, -13})
                                          << SpawnInfo(-10, {40, -13})));
          break;
        case 1:

				default:
					list.push_back(BulletInfo(
							Bullet::BASIC40, Texture::ARROWAQUA, SpawnInfo(0, {0, -13})));
      }
      return list;
    },
		[](EntityPlayer* player)->const SFX& {
      switch (player->level) {
        default:
        case 1:
          return SFX::FIRE1;
        case 2:
          return SFX::FIRE1;
        case 3:
          return SFX::FIRE1;
        case 4:
          return SFX::FIRE1;
      }
    });

const Character Character::PRYSMA("Character: Prysma",
																	Texture::PRYSMA,
																	15,
																	8,
																	[](EntityPlayer* player)
																			->const List<BulletInfo> {
																		return List<BulletInfo>();
																	},
																	[](EntityPlayer* player)->const SFX& {
	switch (player->level) {
		default:
		case 1:
			return SFX::FIRE1;
		case 2:
			return SFX::FIRE1;
		case 3:
			return SFX::FIRE1;
		case 4:
			return SFX::FIRE1;
	}
});

const Character Character::ANEKHANDA("Character: Anekhanda",
																		 Texture::ANEKHANDA,
																		 8,
																		 6,
																		 [](EntityPlayer* player)
																				 ->const List<BulletInfo> {
																			 return List<BulletInfo>();
																		 },
																		 [](EntityPlayer* player)->const SFX& {
	switch (player->level) {
		default:
		case 1:
			return SFX::FIRE1;
		case 2:
			return SFX::FIRE1;
		case 3:
			return SFX::FIRE1;
		case 4:
			return SFX::FIRE1;
	}
});
