#ifndef ALIAS_H
#define ALIAS_H

#include <QDebug>
#include <functional>
#include <list>
#include <map>
#include <random>

using String = std::string;

template <class T>
using List = std::list<T>;

template <class T>
using Array = std::vector<T>;

template <class T, class V>
using Map = std::map<T, V>;

template <class T>
using AI = std::function<void(T*)>;

namespace Random {
int getInt(void);
}

#endif  // ALIAS_H
