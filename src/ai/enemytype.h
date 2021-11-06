#ifndef ENEMIES_H
#define ENEMIES_H

#include <QPointF>
#include <functional>

class Texture;
class Enemy;

using EnemyAI = std::function<void(Enemy*)>;

struct EnemyInfo {
	const Texture& texture;
	const EnemyAI ai;
	const int health;

	Enemy* spawn(const QPointF&) const;
};

namespace Enemies {
extern const EnemyInfo ENEMYTEST;
}

#endif  // ENEMIES_H
