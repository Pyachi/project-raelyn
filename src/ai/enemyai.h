#ifndef ENEMIES_H
#define ENEMIES_H

#include "alias.h"
#include "src/assets/texture.h"
#include <QPointF>

class Enemy;
class UUID;

enum EnemyType {
	ENEMYTEST,
};

struct EnemyInfo {
	const Texture& texture;
	const AI<Enemy> ai;
	const int health;

	Enemy* spawn(const QPointF&, UUID) const;
};

namespace Enemies {
extern const EnemyInfo get(EnemyType);
}

#endif  // ENEMIES_H
