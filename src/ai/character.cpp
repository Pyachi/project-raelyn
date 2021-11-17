#include "character.h"
#include "entityplayer.h"
#include "sfx.h"
#include "texture.h"

Array<Ref<Character> > Character::list;

const Character Character::PYACHI(
		"Character: Pyachi",
    Texture::PYACHI,
    10,
    3,
		[](EntityPlayer* player) -> const List<BulletInfo> {
      List<BulletInfo> list;

      switch (player->level) {
        case 4:

        case 3:

        case 2:
          if (player->focus)
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
                                      SpawnInfo(0, {10, -13})
                                          << SpawnInfo(0, {-10, -13})));
          else
						list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
                                      SpawnInfo(10, {10, -13})
                                          << SpawnInfo(-10, {-10, -13})));
        case 1:
        default:
					list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
																		SpawnInfo(0, {0, -13})));
      }
      return list;
    },
		[](EntityPlayer* player) -> const SFX& {
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
		[](EntityPlayer* player) -> const SFX& {
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

const Character Character::PRYSMA(
		"Character: Prysma",
		Texture::PRYSMA,
		15,
		8,
		[](EntityPlayer* player) -> const List<BulletInfo> {
			return List<BulletInfo>();
		},
		[](EntityPlayer* player) -> const SFX& {
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

const Character Character::ANEKHANDA(
		"Character: Anekhanda",
		Texture::ANEKHANDA,
		8,
		6,
		[](EntityPlayer* player) -> const List<BulletInfo> {
			return List<BulletInfo>();
		},
		[](EntityPlayer* player) -> const SFX& {
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
