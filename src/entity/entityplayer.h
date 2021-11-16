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
	int power;

	void addPower(void) {
		if (level != 4)
			power++;
		else
			User::addCurrentScore(500);
	}

 private:
  QGraphicsSimpleTextItem display;
  String name;
  bool firing;

  int health;
  int invFrames;
};

#endif  // ENTITYPLAYER_H
