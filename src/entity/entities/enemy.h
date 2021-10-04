#ifndef ENEMY_H
#define ENEMY_H

#include "playerhitbox.h"
#include "src/entity/types/aientity.h"
#include "src/entity/types/baseentity.h"
#include "src/entity/types/collidableentity.h"

class Enemy : public AIEntity<Enemy>, public CollidableEntity {
 public:
	Enemy(Game*, Texture, QPoint, std::function<void(Enemy*)>, int);

	void decHealth();
	int getHealth();

	QList<CollidableEntity*> getValidHits();

 private:
	int health;

	void tick() override;
};

#endif  // ENEMY_H
