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
				case 1:
					if (focus)
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::PLAYER_BASIC);
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::PLAYER_BASIC);
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
				case 1:
					if (focus)
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::PLAYER_HOMING);
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::PLAYER_HOMING);
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
		case DAESCH:
			switch (level) {
				case 1:
					if (focus)
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::FLOWERCIRCLE);
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::FLOWERCIRCLE);
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
		case ANEKHANDA:
			switch (level) {
				case 1:
					if (focus)
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::SPRAY);
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullets(BulletPatterns::SPRAY);
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
