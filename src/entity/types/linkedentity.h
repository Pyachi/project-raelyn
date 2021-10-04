#ifndef LINKEDENTITY_H
#define LINKEDENTITY_H

#include "baseentity.h"

class LinkedEntity : virtual public BaseEntity {
 public:
	LinkedEntity(Game*, Texture, QPoint, BaseEntity*);

	BaseEntity* getOwner();

 protected:
	BaseEntity* owner;
};

#endif  // LINKEDENTITY_H
