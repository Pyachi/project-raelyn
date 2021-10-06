#ifndef BULLET_H
#define BULLET_H

#include "playerhitbox.h"
#include "src/entity/types/aientity.h"
#include "src/entity/types/baseentity.h"
#include "src/entity/types/collidableentity.h"
#include "src/entity/types/linkedentity.h"

class Bullet : public LinkedEntity,
							 public AIEntity<Bullet>,
							 public CollidableEntity {
 public:
	Bullet(Game*,
				 Texture,
				 QPoint,
				 BaseEntity*,
				 std::function<void(Bullet*)>,
				 double);

 private:
	void tick() override;
};

#endif  // BULLET_H
