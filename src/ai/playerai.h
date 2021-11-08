#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include <QString>
#include "alias.h"

class Texture;
class Player;

enum PlayerType {
	PYACHI,
	AERON,
	DAESCH,
	ANEKHANDA
};

namespace PlayerInfo {
extern const QString getName(PlayerType);
extern PlayerType fromName(const QString&);
extern const Texture& getTexture(PlayerType);
extern const AI<Player> getShootingPattern(PlayerType, int, bool);
extern int getSpeed(PlayerType);
extern int getFocusSpeed(PlayerType);
};  // namespace PlayerInfo

#endif  // PLAYERTYPE_H
