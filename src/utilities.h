#ifndef UTILITIES_H
#define UTILITIES_H

#include <QPointF>
#include <QSizeF>

class BaseEntity;
struct BulletInfo;

namespace Util {
extern bool confineToPlayableArea(QPointF&, QSizeF);
extern void bulletCircle(BaseEntity*, BulletInfo&, int, double = 0);
}  // namespace Util

#endif  // UTILITIES_H
