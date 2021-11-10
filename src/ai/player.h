#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include <QString>
#include "util.h"
#include "src/assets/texture.h"

enum PlayerType { PYACHI, AERON, DAESCH, ANEKHANDA };

class EntityPlayer;

namespace Players {
extern Tex getTexture(PlayerType);
extern const AI<EntityPlayer> getShootingPattern(PlayerType, int, bool);
extern int getSpeed(PlayerType);
extern int getFocusSpeed(PlayerType);
};  // namespace Players

#endif  // PLAYERTYPE_H
