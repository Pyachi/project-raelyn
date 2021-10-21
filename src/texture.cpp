#include "texture.h"

Texture::Texture(const QString& texture, int zValue)
		: texture(texture), zValue(zValue) {}

const Texture Texture::PLAYERHITBOX = Texture(":/images/player_hitbox.png", 4);
const Texture Texture::PLAYER1 = Texture(":/images/player.png", 3);
const Texture Texture::ENEMY1 = Texture(":/images/enemy.png", 3);
const Texture Texture::PLAYERBULLETBASIC =
		Texture(":/images/player_bullet.png", 2);
const Texture Texture::BULLETROUND = Texture(":/images/bulletRound.png", 2);
const Texture Texture::BULLETELLIPSE = Texture(":/images/bulletEllipse.png", 2);
const Texture Texture::BACKGROUND = Texture(":/images/background.png", 5);
