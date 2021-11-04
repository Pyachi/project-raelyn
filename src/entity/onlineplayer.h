#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include "entity.h"

class OnlinePlayer : public Entity {
 public:
	OnlinePlayer(const Texture&, const QPointF&);

	void tick() override;
};

#endif  // ONLINEPLAYER_H
