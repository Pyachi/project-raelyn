#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

enum Tex {
	TEXHITBOX,
	TEXPYACHI,
	TEXAERON,
	TEXDAESCH,
	TEXANEKHANDA,
	TEXENEMY1,
	TEXPLAYERBULLET,
	TEXBULLETROUND,
	TEXBULLETELLIPSE,
	BACKGROUND,
	TITLE,
};

struct Texture {
  const QString texture;
  const int zValue;
	static const Texture get(Tex);
};

#endif  // TEXTURES_H
