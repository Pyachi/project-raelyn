#ifndef ENTITYBOSS_H
#define ENTITYBOSS_H

#include "entity.h"

class EntityBoss : public Entity {
 public:
  EntityBoss(const Texture& tex,
             const UID& id,
             const Array<int>& health,
             const AI<EntityBoss>& ai);

  int health;
  int phase;

  void kill(void);
  void advancePhase(void);

 private:
  const Array<int> totalHealth;
  const AI<EntityBoss>& ai;

  void tick(void) override;
};

#endif  // ENTITYBOSS_H
