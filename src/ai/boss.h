#ifndef BOSS_H
#define BOSS_H

#include "util.h"

enum Boss {
	BOSS_LVL1MINI,
	BOSS_LVL1,
	BOSS_LVL2MINI,
	BOSS_LVL2,
	BOSS_LVL3MINI,
	BOSS_LVL3
};

class EntityBoss;
class UID;

namespace Bosses {
extern EntityBoss* spawn(Boss boss, UID id, const QPointF& loc);
}

#endif  // BOSS_H
