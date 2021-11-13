#include "player.h"
#include "Entity"

namespace Players {
Texture getTexture(PlayerType type) {
  switch (type) {
    case PYACHI:
      return TEXTURE_PYACHI;
    case AERON:
      return TEXTURE_AERON;
    case PRYSMA:
      return TEXTURE_PRYSMA;
    case ANEKHANDA:
      return TEXTURE_ANEKHANDA;
  }
}

const AI<EntityPlayer> getShootingPattern(PlayerType type,
                                          int level,
                                          bool focus) {
  switch (type) {
    case PYACHI:
      switch (level) {
        default:
        case 1:
          if (focus)
            return [](EntityPlayer* player) {
              player->fireBullet(BulletInfo(0, {0, -13}), AI_PLAYERBASIC,
                                 TEXTURE_BULLET_ELLIPSE_YELLOW);
            };
          else
            return [](EntityPlayer* player) {
              player->fireBullet(BulletInfo(0, {0, -13}), AI_PLAYERBASIC,
                                 TEXTURE_BULLET_ELLIPSE_YELLOW);
            };
        case 2:
          if (focus)
            return [](EntityPlayer* player) {
              player->fireBullets(
                  BulletInfo(0, {0, -13})
                      << BulletInfo(0, {5, -13}) << BulletInfo(0, {-5, -13}),
                  AI_PLAYERBASIC, TEXTURE_BULLET_ELLIPSE_YELLOW);
            };
          else
            return [](EntityPlayer* player) {
              player->fireBullets(
                  BulletInfo(0, {0, -13})
                      << BulletInfo(0, {10, -13}) << BulletInfo(0, {-10, -13}),
                  AI_PLAYERBASIC, TEXTURE_BULLET_ELLIPSE_YELLOW);
            };
        case 3:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 4:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
      }
    case AERON:
      switch (level) {
        default:
        case 1:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 2:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 3:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 4:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
      }
    case PRYSMA:
      switch (level) {
        default:
        case 1:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 2:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 3:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 4:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
      }
    case ANEKHANDA:
      switch (level) {
        default:
        case 1:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 2:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 3:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
        case 4:
          if (focus)
            return [](EntityPlayer* player) {};
          else
            return [](EntityPlayer* player) {};
      }
  }
}

int getSpeed(PlayerType type) {
  switch (type) {
    case PYACHI:
      return 10;
    case AERON:
      return 12;
    case PRYSMA:
      return 15;
    case ANEKHANDA:
      return 8;
  }
}

int getFocusSpeed(PlayerType type) {
  switch (type) {
    case PYACHI:
      return 3;
    case AERON:
      return 5;
    case PRYSMA:
      return 8;
    case ANEKHANDA:
      return 6;
  }
}
}  // namespace Players
