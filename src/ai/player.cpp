#include "player.h"
#include "bulletpattern.h"
#include "src/assets/texture.h"
#include "src/entity/entitybullet.h"
#include "src/entity/entityplayer.h"

namespace Players {
Texture getTexture(PlayerType type) {
	switch (type) {
		case PYACHI:
			return TEXTURE_PLAYERTEMP;
		case AERON:
			return TEXTURE_PLAYERTEMP;
		case DAESCH:
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
							if (player->cycle(5))
								switch ((player->getAge() / 5) % 8) {
									default:
									case 0:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_RED,
																				0,
																				{0, 0},
																				5);
										break;
									case 1:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_ORANGE,
																				0,
																				{0, 0},
																				5);
										break;
									case 2:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_YELLOW,
																				0,
																				{0, 0},
																				5);
										break;
									case 3:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_GREEN,
																				0,
																				{0, 0},
																				5);
										break;
									case 4:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_AQUA,
																				0,
																				{0, 0},
																				5);
										break;
									case 5:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_BLUE,
																				0,
																				{0, 0},
																				5);
										break;
									case 6:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_PURPLE,
																				0,
																				{0, 0},
																				5);
										break;
									case 7:
										player->fireBullets(PATTERN_PLAYERHOMINGX2C,
																				TEXTURE_BULLET_STAR_MAGENTA,
																				0,
																				{0, 0},
																				5);
										break;
								}
						};
					else
						return [](EntityPlayer* player) {
							player->fireBullets(PATTERN_PLAYERBASIC,
																	TEXTURE_BULLET_ARROW_RED);
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
