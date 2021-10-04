#ifndef AIENTITY_H
#define AIENTITY_H

#include <functional>

#include "baseentity.h"

template <class T>
class AIEntity : virtual public BaseEntity {
 public:
	AIEntity(Game* game, Texture texture, QPoint spawn, std::function<void(T*)>);

 protected:
	std::function<void(T*)> tick;
};

template <class T>
AIEntity<T>::AIEntity(Game* game,
											Texture texture,
											QPoint spawn,
											std::function<void(T*)> ai)
		: BaseEntity(game, texture, spawn) {
	this->tick = ai;
}

#endif  // AIENTITY_H
