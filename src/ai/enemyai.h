#ifndef ENEMIES_H
#define ENEMIES_H

#include "alias.h"
#include "src/assets/texture.h"
#include <QPointF>

class Enemy;

struct EnemyInfo {
	const Texture& texture;
	const AI<Enemy> ai;
	const int health;

	Enemy* spawn(const QPointF&) const;
};

namespace Enemies {
extern const EnemyInfo ENEMYTEST;
}

#endif  // ENEMIES_H
