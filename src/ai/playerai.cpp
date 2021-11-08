#include "playerai.h"
#include "bulletpattern.h"
#include "src/assets/texture.h"
#include "src/entity/bullet.h"
#include "src/entity/player.h"

namespace Players {
const QString getName(PlayerType type) {
	switch (type) {
		case PYACHI:
			return "Pyachi";
		case AERON:
			return "Aeron";
		case DAESCH:
			return "Daesch";
		case ANEKHANDA:
			return "Anekhanda";
	}
}

PlayerType fromName(const QString& name) {
	if (name == "Aeron")
		return AERON;
	if (name == "Daesch")
		return DAESCH;
	if (name == "Anekhanda")
		return ANEKHANDA;
	return PYACHI;
}

PlayerType fromInt(int i) {
	switch (i) {
		case 1:
			return AERON;
		case 2:
			return DAESCH;
		case 3:
			return ANEKHANDA;
		default:
			return PYACHI;
	}
}

const Texture& getTexture(PlayerType type) {
	switch (type) {
		case PYACHI:
		case AERON:
		case DAESCH:
		case ANEKHANDA:
			return Textures::PYACHI;
	}
}

const AI<Player> getShootingPattern(PlayerType type, int level, bool focus) {
	switch (type) {
		case PYACHI:
			switch (level) {
				case 1:
					if (focus)
						return [](Player* player) {
							player->fireBullets(BulletPatterns::PLAYER_HOMING);
						};
					else
						return [](Player* player) {
							player->fireBullets(BulletPatterns::PLAYER_BASIC);
						};
				case 2:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 3:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 4:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
			}
		case AERON:
			switch (level) {
				case 1:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 2:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 3:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 4:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
			}
		case DAESCH:
			switch (level) {
				case 1:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 2:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 3:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 4:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
			}
		case ANEKHANDA:
			switch (level) {
				case 1:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 2:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 3:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
				case 4:
					if (focus)
						return [](Player* player) {};
					else
						return [](Player* player) {};
			}
	}
}

int getSpeed(PlayerType type) {
	switch (type) {
		case PYACHI:
			return 10;
		case AERON:
			return 12;
		case DAESCH:
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
		case DAESCH:
			return 8;
		case ANEKHANDA:
			return 6;
	}
}
}
