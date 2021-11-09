#include "texture.h"

const Texture Texture::get(Tex texture) {
	switch (texture) {
		case TEXHITBOX:
			return {":/textures/player_hitbox.png", 4};
		case TEXPYACHI:
			return {":/textures/player.png", 3};
		case TEXAERON:
			return {":/textures/player.png", 3};
		case TEXDAESCH:
			return {":/textures/player.png", 3};
		case TEXANEKHANDA:
			return {":/textures/player.png", 3};
		case TEXENEMY1:
			return {":/textures/enemy.png", 3};
		case TEXPLAYERBULLET:
			return {":/textures/player_bullet.png", 2};
		case TEXBULLETROUND:
			return {":/textures/bulletRound.png", 2};
		case TEXBULLETELLIPSE:
			return {":/textures/bulletEllipse.png", 2};
		case BACKGROUND:
			return {":/textures/background.png", 5};
		case TITLE:
			return {":/textures/title.png", 0};
	}
}
