#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

struct Texture {
	Texture(QString, int);

	QString texture;
	int zValue;
};

namespace Textures {
extern Texture playerHitbox;
extern Texture player1;
extern Texture enemy1;
extern Texture playerBullet1;
extern Texture enemyBullet1;
extern Texture enemyBullet2;
};  // namespace Textures

#endif  // TEXTURES_H
