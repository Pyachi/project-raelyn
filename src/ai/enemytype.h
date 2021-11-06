#ifndef ENEMIES_H
#define ENEMIES_H

#include <QPointF>
#include <functional>

class Texture;
class Enemy;

using EnemyAI = std::function<void(Enemy*)>;

class EnemyType {
 public:
	static const EnemyType ENEMYTEST;

	const Texture& texture;
	const EnemyAI ai;
	const int health;

	Enemy* spawn(const QPointF&) const;

 private:
	EnemyType(const Texture&, const EnemyAI&, int = 50);
};

#endif  // ENEMIES_H
