#ifndef ENTITYENEMY_H
#define ENTITYENEMY_H

#include "entity.h"

class EntityEnemy : public Entity {
 public:
  EntityEnemy(const Texture& tex,
              const UID& id,
              int health,
              const AI<EntityEnemy>& ai);

  int health;

	void damage(int damage) override;
  void kill(void);

 private:
  const AI<EntityEnemy> ai;

  void tick(void) override;
};

#endif  // ENTITYENEMY_H
