#include "textures.h"

Texture::Texture(QString texture, int zValue)
		: texture(texture), zValue(zValue) {}

Texture Textures::playerHitbox = Texture(":/images/player_hitbox.png", 4);
Texture Textures::player1 = Texture(":/images/player.png", 3);
Texture Textures::enemy1 = Texture(":/images/enemy.png", 3);
Texture Textures::playerBasic = Texture(":/images/player_bullet.png", 2);
Texture Textures::bulletRound = Texture(":/images/bulletRound.png", 2);
Texture Textures::bulletEllipse = Texture(":/images/bulletEllipse.png", 2);
