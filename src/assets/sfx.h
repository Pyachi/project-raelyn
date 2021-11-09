#ifndef SFX_H
#define SFX_H

#include <QString>

enum SoundEffect {
	COLLECT_1,          // 0
	COLLECT_2,          // 1
	COLLECT_3,          // 2
	EXPL_HEAVY_1,       // 3
	EXPL_HEAVY_2,       // 4
	EXPL_HEAVY_3,       // 5
	EXPL_HEAVY_4,       // 6
	EXPL_LIGHT_1,       // 7
	EXPL_LIGHT_2,       // 8
	EXPL_LIGHT_3,       // 9
	EXPL_MED_1,         // 10
	EXPL_MED_2,         // 11
	EXPL_MED_3,         // 12
	EXPL_SUPERHEAVY_1,  // 13
	EXPL_SUPERHEAVY_2,  // 14
	HIT_1,              // 15
	HIT_2,              // 16
	HIT_3,              // 17
	LASER_1,            // 18
	MISSILE_1,          // 19
	MISSILE_2,          // 20
	MISSILE_3,          // 21
	POWERUP_1,          // 22
	POWERUP_2,          // 23
	POWERUP_3,          // 24
	SELECT_1,           // 25
	SELECT_2,           // 26
};

namespace SFX {
extern double volume;
extern const QString get(SoundEffect);
extern void playSound(SoundEffect, double = 0);
};  // namespace SFX

#endif  // SFX_H
