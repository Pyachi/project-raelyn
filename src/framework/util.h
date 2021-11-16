#ifndef ALIAS_H
#define ALIAS_H

#include <QDebug>
#include <QPointF>
#include <QVector2D>
#include <QtMath>
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

template <class T>
using Func = std::function<T>;

template <class T>
using Ref = std::reference_wrapper<T>;

namespace Random {
int getInt(void);
int getInt(int max);
float getFloat(float max);
}  // namespace Random

#endif  // ALIAS_H
