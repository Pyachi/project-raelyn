#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H

#include <functional>

class Texture;
class Player;

using PlayerAI = std::function<void(Player*)>;

enum PlayerType {
	PYACHI,
	AERON,
	DAESCH,
	ANEKHANDA
};

class PlayerInfo {
 public:
	static const Texture& getTexture(PlayerType);
	static const PlayerAI getShootingPattern(PlayerType, int, bool);
	static int getSpeed(PlayerType);
	static int getFocusSpeed(PlayerType);
};

#endif  // PLAYERTYPE_H
