#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

enum Texture {
	// Round Bullets
	TEXTURE_BULLET_ROUND_RED,
	TEXTURE_BULLET_ROUND_ORANGE,
	TEXTURE_BULLET_ROUND_YELLOW,
	TEXTURE_BULLET_ROUND_GREEN,
	TEXTURE_BULLET_ROUND_AQUA,
	TEXTURE_BULLET_ROUND_BLUE,
	TEXTURE_BULLET_ROUND_PURPLE,
	TEXTURE_BULLET_ROUND_MAGENTA,

	// Elliptical Bullets
	TEXTURE_BULLET_ELLIPSE_RED,
	TEXTURE_BULLET_ELLIPSE_ORANGE,
	TEXTURE_BULLET_ELLIPSE_YELLOW,
	TEXTURE_BULLET_ELLIPSE_GREEN,
	TEXTURE_BULLET_ELLIPSE_AQUA,
	TEXTURE_BULLET_ELLIPSE_BLUE,
	TEXTURE_BULLET_ELLIPSE_PURPLE,
	TEXTURE_BULLET_ELLIPSE_MAGENTA,

	// Arrowhead Bullets
	TEXTURE_BULLET_ARROW_RED,
	TEXTURE_BULLET_ARROW_ORANGE,
	TEXTURE_BULLET_ARROW_YELLOW,
	TEXTURE_BULLET_ARROW_GREEN,
	TEXTURE_BULLET_ARROW_AQUA,
	TEXTURE_BULLET_ARROW_BLUE,
	TEXTURE_BULLET_ARROW_PURPLE,
	TEXTURE_BULLET_ARROW_MAGENTA,

	// Star Bullets
	TEXTURE_BULLET_STAR_RED,
	TEXTURE_BULLET_STAR_ORANGE,
	TEXTURE_BULLET_STAR_YELLOW,
	TEXTURE_BULLET_STAR_GREEN,
	TEXTURE_BULLET_STAR_AQUA,
	TEXTURE_BULLET_STAR_BLUE,
	TEXTURE_BULLET_STAR_PURPLE,
	TEXTURE_BULLET_STAR_MAGENTA,

	// Lazer Bullets
	TEXTURE_BULLET_LAZER_RED,
	TEXTURE_BULLET_LAZER_ORANGE,
	TEXTURE_BULLET_LAZER_YELLOW,
	TEXTURE_BULLET_LAZER_GREEN,
	TEXTURE_BULLET_LAZER_AQUA,
	TEXTURE_BULLET_LAZER_BLUE,
	TEXTURE_BULLET_LAZER_PURPLE,
	TEXTURE_BULLET_LAZER_MAGENTA,

	// Collectables
	TEXTURE_COLLECTABLE_POWER,
	TEXTURE_COLLECTABLE_POINTS,

	// Temporary
	TEXTURE_ENEMYTEMP,
	TEXTURE_BACKGROUNDTEMP,
	TEXTURE_TITLETEMP,
	TEXTURE_PLAYERTEMP,

	// Players
	TEXTURE_PLAYER_HITBOX,
};

namespace Textures {
const QString getTexture(Texture);
int getZValue(Texture);
}

#endif  // TEXTURES_H
