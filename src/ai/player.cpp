#include "player.h"
#include "Entity"

namespace Players {
Texture getTexture(PlayerType type) {
	switch (type) {
		case PYACHI:
			return TEXTURE_PLAYERTEMP;
		case AERON:
			return TEXTURE_PLAYERTEMP;
		case PRYSMA:
			return TEXTURE_PLAYERTEMP;
		case ANEKHANDA:
			return TEXTURE_PLAYERTEMP;
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
							player->fireBullet(BulletInfo(),
																 AI_PLAYERBASIC,
																 TEXTURE_BULLET_ARROW_RED,
																 180,
																 {0, 0},
																 2);
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullet(BulletInfo(),
																 AI_PLAYERBASIC,
																 TEXTURE_BULLET_ARROW_RED,
																 180,
																 {0, 0},
																 2);
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
