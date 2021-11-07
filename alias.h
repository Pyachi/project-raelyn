#ifndef ALIAS_H
#define ALIAS_H

#include <list>
#include <set>
#include <queue>
#include <map>
#include <functional>

template <class T>
using List = std::list<T>;

template <class T>
using Queue = std::queue<T>;

template <class T, class V>
using Map = std::map<T, V>;

template <class T>
using AI = std::function<void(T*)>;

#endif  // ALIAS_H
