#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

class Texture {
 public:
	static const Texture PLAYERHITBOX;
	static const Texture PLAYER1;
	static const Texture ENEMY1;
	static const Texture PLAYERBULLETBASIC;
	static const Texture BULLETROUND;
	static const Texture BULLETELLIPSE;

	const QString texture;
	const int zValue;

 private:
	Texture(const QString&, int);
};

#endif  // TEXTURES_H
