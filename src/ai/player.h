#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include "texture.h"
#include "util.h"

enum PlayerType {
	PYACHI,
	AERON,
	PRYSMA,
	ANEKHANDA
};

class EntityPlayer;

namespace Players {
extern Texture getTexture(PlayerType type);
extern const AI<EntityPlayer> getShootingPattern(PlayerType type,
																								 int level,
																								 bool focus);
extern int getSpeed(PlayerType type);
extern int getFocusSpeed(PlayerType type);
};  // namespace Players

#endif  // PLAYERTYPE_H
