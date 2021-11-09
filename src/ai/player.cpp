#include "player.h"
#include "bulletpattern.h"
#include "src/assets/texture.h"
#include "src/entity/entitybullet.h"
#include "src/entity/entityplayer.h"

namespace Players {
Tex getTexture(PlayerType type) {
	switch (type) {
		case PYACHI:
			return TEXPYACHI;
		case AERON:
			return TEXAERON;
		case DAESCH:
			return TEXDAESCH;
		case ANEKHANDA:
			return TEXANEKHANDA;
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
							player->fireBullets(PATTERN_PLAYERBASICX5C);
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullets(PATTERN_PLAYERBASIC);
						};
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
		case DAESCH:
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
}  // namespace Players
