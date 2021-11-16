#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "character.h"
#include "entity.h"

class EntityPlayer : public Entity {
 public:
  EntityPlayer(const Character& character,
               const String& name,
               const UID& id,
               EntityType type = PLAYER);

  void tick(void) override;

  QGraphicsPixmapItem hitbox;
  const Character& character;
  bool focus;
  int level;

  void addPower(void) { power++; }

 private:
  QGraphicsSimpleTextItem display;
  String name;
  bool firing;
  int power;
  int health;
  int invFrames;
};

#endif  // ENTITYPLAYER_H
