#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

struct Texture {
	const QString texture;
	const int zValue;
};

namespace Textures {
extern const Texture PLAYERHITBOX;
extern const Texture PYACHI;
extern const Texture AERON;
extern const Texture DAESCH;
extern const Texture ANEKHANDA;
extern const Texture ENEMY1;
extern const Texture PLAYERBULLETBASIC;
extern const Texture BULLETROUND;
extern const Texture BULLETELLIPSE;
extern const Texture BACKGROUND;
extern const Texture TITLE;
}  // namespace Textures

#endif  // TEXTURES_H
