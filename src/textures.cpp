#include "textures.h"

Texture::Texture(QString texture, int zValue)
		: texture(texture), zValue(zValue) {}

Texture Textures::playerHitbox = Texture(":/images/player_hitbox.png", 4);
Texture Textures::player1 = Texture(":/images/player.png", 3);
Texture Textures::enemy1 = Texture(":/images/enemy.png", 3);
Texture Textures::playerBullet1 = Texture(":/images/player_bullet.png", 2);
Texture Textures::enemyBullet1 = Texture(":/images/enemy_bullet_1.png", 2);
Texture Textures::enemyBullet2 = Texture(":/images/enemy_bullet_2.png", 2);
