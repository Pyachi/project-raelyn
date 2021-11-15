#include "character.h"
#include "entityplayer.h"
#include "texture.h"

Array<Ref<Character>> Character::list;

const Character Character::PYACHI(
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
          list.push_back(BulletInfo(Bullet::BASIC40, Texture::ELLIPSEYELLOW,
                                    SpawnInfo(0, {0, -13})));
      }
      return list;
    });

const Character Character::AERON(Texture::AERON,
                                 12,
                                 5,
                                 [](EntityPlayer* player)
                                     -> const List<BulletInfo> {
                                   return List<BulletInfo>();
                                 });

const Character Character::PRYSMA(Texture::PRYSMA,
                                  15,
                                  8,
                                  [](EntityPlayer* player)
                                      -> const List<BulletInfo> {
                                    return List<BulletInfo>();
                                  });

const Character Character::ANEKHANDA(Texture::ANEKHANDA,
                                     8,
                                     6,
                                     [](EntityPlayer* player)
                                         -> const List<BulletInfo> {
                                       return List<BulletInfo>();
                                     });
