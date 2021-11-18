#ifndef ENTITYBOSS_H
#define ENTITYBOSS_H

#include "entity.h"
#include <QGraphicsProxyWidget>
#include <QProgressBar>

class ProgressBar : public QProgressBar {
 public:
	ProgressBar();

	void paintEvent(QPaintEvent* e) override;
};

class EntityBoss : public Entity {
 public:
  EntityBoss(const Texture& tex,
             const UID& id,
             const Array<int>& health,
             const AI<EntityBoss>& ai);

  int health;
	ushort phase;

  void kill(void);
  void advancePhase(void);

 private:
	~EntityBoss() override;

  const Array<int> totalHealth;
  const AI<EntityBoss>& ai;
	int invFrames = 0;

	QGraphicsProxyWidget healthBarDisplay;
	ProgressBar healthBar;

  void tick(void) override;
};

#endif  // ENTITYBOSS_H
