#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "character.h"
#include "entity.h"

class EntityPlayer : public Entity {
 public:
  EntityPlayer(const Character& character,
               const QString& name,
               const UID& id,
               EntityType type = PLAYER);

  void tick(void) override;

  QGraphicsPixmapItem hitbox;
  const Character& character;
  bool focus;
  int level;

	void addPower(void) { power++; }
	void addPoints(int count) { points += count; }

 private:
  QGraphicsSimpleTextItem display;
  QString name;
  bool firing;
  int power;
  int points;
  int health;
  int invFrames;
};

#endif  // ENTITYPLAYER_H
