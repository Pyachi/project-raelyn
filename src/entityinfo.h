#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <functional>

struct Texture;

template <class T>
using EntityAI = std::function<void(T*)>;

template <class T>
struct EntityInfo {
	EntityInfo(Texture&, EntityAI<T>&);

	Texture& texture;
	EntityAI<T>& ai;
};

template <class T>
EntityInfo<T>::EntityInfo(Texture& texture, EntityAI<T>& ai)
		: texture(texture), ai(ai) {}

#endif  // ENTITYINFO_H
