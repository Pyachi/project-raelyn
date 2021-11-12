#ifndef ENTITYBOSS_H
#define ENTITYBOSS_H

#include "entity.h"

class EntityBoss : public Entity {
 public:
	EntityBoss(Texture tex,
						 UID id,
						 int phaseHealth,
						 int phaseCount,
						 AI<EntityBoss> ai);

	int health;
	int phase;

	void kill(void);
	void advancePhase(void);

 private:
	int phaseHealth;
	const AI<EntityBoss> ai;

	void tick(void) override;
};

#endif  // ENTITYBOSS_H
