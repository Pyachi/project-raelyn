#ifndef ALIAS_H
#define ALIAS_H

#include <list>
#include <set>
#include <queue>
#include <map>
#include <functional>
#include <QDebug>

template <class T>
using List = std::list<T>;

template <class T>
using AI = std::function<void(T*)>;

#endif  // ALIAS_H
