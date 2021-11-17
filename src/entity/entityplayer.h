#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "character.h"
#include "entity.h"
#include "user.h"

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
	int invFrames;

 private:
  QGraphicsSimpleTextItem display;
	const String name;
  bool firing;
};

#endif  // ENTITYPLAYER_H
