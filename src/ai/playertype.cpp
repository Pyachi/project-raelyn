#include "playertype.h"
#include "src/entity/bullet.h"
#include "src/entity/player.h"
#include "bulletpattern.h"
#include "src/assets/texture.h"

const Texture& PlayerInfo::getTexture(PlayerType type) {
	switch (type) {
		case PYACHI:
		case AERON:
		case DAESCH:
		case ANEKHANDA:
			return Textures::PYACHI;
	}
}

const PlayerAI PlayerInfo::getShootingPattern(PlayerType type,
																							int level,
																							bool focus) {
	switch (type) {
		case PYACHI:
			switch (level) {
				case 1:
					if (focus)
						return [](Player* player) {
							foreach(Bullet * bullet,
											player->fireBullet(BulletPattern::PLAYER_BASIC)) {
								bullet->setOpacity(0.25);
							}
						};
					else
						return [](Player* player) {
							foreach(Bullet * bullet,
											player->fireBullet(BulletPattern::PLAYER_BASIC)) {
								bullet->setOpacity(0.25);
							}
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

int PlayerInfo::getSpeed(PlayerType type) {
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

int PlayerInfo::getFocusSpeed(PlayerType type) {
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
