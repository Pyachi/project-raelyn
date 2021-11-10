#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include <QString>
#include "src/assets/texture.h"
#include "util.h"

enum PlayerType { PYACHI, AERON, PRYSMA, ANEKHANDA };

class EntityPlayer;

namespace Players {
extern Texture getTexture(PlayerType);
extern const AI<EntityPlayer> getShootingPattern(PlayerType, int, bool);
extern int getSpeed(PlayerType);
extern int getFocusSpeed(PlayerType);
};  // namespace Players

#endif  // PLAYERTYPE_H
