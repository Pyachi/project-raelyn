#include "texture.h"

Texture::Texture(const QString& texture, int zValue)
		: texture(texture), zValue(zValue) {}

const Texture Texture::PLAYERHITBOX = Texture(":/images/images/player_hitbox.png", 4);
const Texture Texture::PLAYER1 = Texture(":/images/images/player.png", 3);
const Texture Texture::ENEMY1 = Texture(":/images/images/enemy.png", 3);
const Texture Texture::PLAYERBULLETBASIC =
		Texture(":/images/images/player_bullet.png", 2);
const Texture Texture::BULLETROUND = Texture(":/images/images/bulletRound.png", 2);
const Texture Texture::BULLETELLIPSE = Texture(":/images/images/bulletEllipse.png", 2);
const Texture Texture::BACKGROUND = Texture(":/images/images/background.png", 5);
