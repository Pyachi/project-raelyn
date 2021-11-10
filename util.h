#ifndef ALIAS_H
#define ALIAS_H

#include <list>
#include <set>
#include <queue>
#include <map>
#include <functional>
#include <QDebug>
#include <chrono>
#include <random>

template <class T>
using List = std::list<T>;

template <class T>
using Array = std::vector<T>;

template <class T>
using AI = std::function<void(T*)>;

namespace Random {
int getInt(void);
}

#endif  // ALIAS_H
