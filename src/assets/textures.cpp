#include "textures.h"

Texture::Texture(QString texture, int zValue) {
	this->texture = texture;
	this->zValue = zValue;
}

QString Texture::getTexture() {
	return texture;
}

int Texture::getZValue() {
	return zValue;
}

Texture Textures::player = Texture(":/images/player.png", 3);
Texture Textures::playerHitbox = Texture(":/images/player_hitbox.png", 4);
Texture Textures::playerBullet = Texture(":/images/player_bullet.png", 2);
Texture Textures::enemy1 = Texture(":/images/enemy.png", 3);
Texture Textures::enemyBullet1 = Texture(":/images/enemy_bullet_1.png", 2);
Texture Textures::enemyBullet2 = Texture(":/images/enemy_bullet_2.png", 2);
