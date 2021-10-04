#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

class Texture {
 public:
	Texture(QString, int);

	QString getTexture();
	int getZValue();

 private:
	QString texture;
	int zValue;
};

namespace Textures {
extern Texture player;
extern Texture playerHitbox;
extern Texture playerBullet;
extern Texture enemy1;
extern Texture enemyBullet1;
extern Texture enemyBullet2;
}  // namespace Textures

#endif  // TEXTURES_H
