#ifndef SFX_H
#define SFX_H

#include <QString>

enum SoundEffect {
	COLLECT_1,
	COLLECT_2,
	COLLECT_3,
	EXPL_HEAVY_1,
	EXPL_HEAVY_2,
	EXPL_HEAVY_3,
	EXPL_HEAVY_4,
	EXPL_LIGHT_1,
	EXPL_LIGHT_2,
	EXPL_LIGHT_3,
	EXPL_MED_1,
	EXPL_MED_2,
	EXPL_MED_3,
	EXPL_SUPERHEAVY_1,
	EXPL_SUPERHEAVY_2,
	HIT_1,
	HIT_2,
	HIT_3,
	LASER_1,
	MISSILE_1,
	MISSILE_2,
	MISSILE_3,
	POWERUP_1,
	POWERUP_2,
	POWERUP_3,
	SELECT_1,
	SELECT_2
};

namespace SFX {
extern double volume;
extern const QString get(SoundEffect);
extern void playSound(SoundEffect, double = 1);
};  // namespace SFX

#endif  // SFX_H
