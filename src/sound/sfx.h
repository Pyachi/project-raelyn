#ifndef SFX_H
#define SFX_H

#include <QString>

class SFX {
 public:
	static const SFX COLLECT_1;
	static const SFX COLLECT_2;
	static const SFX COLLECT_3;
	static const SFX EXPL_HEAVY_1;
	static const SFX EXPL_HEAVY_2;
	static const SFX EXPL_HEAVY_3;
	static const SFX EXPL_HEAVY_4;
	static const SFX EXPL_LIGHT_1;
	static const SFX EXPL_LIGHT_2;
	static const SFX EXPL_LIGHT_3;
	static const SFX EXPL_MED_1;
	static const SFX EXPL_MED_2;
	static const SFX EXPL_MED_3;
	static const SFX EXPL_SUPERHEAVY_1;
	static const SFX EXPL_SUPERHEAVY_2;
	static const SFX HIT_1;
	static const SFX HIT_2;
	static const SFX HIT_3;
	static const SFX LASER_1;
	static const SFX MISSILE_1;
	static const SFX MISSILE_2;
	static const SFX MISSILE_3;
	static const SFX POWERUP_1;
	static const SFX POWERUP_2;
	static const SFX POWERUP_3;
	static const SFX SELECT_1;
	static const SFX SELECT_2;

	const QString sound_effect;

 private:
	SFX(const QString&);
};

#endif  // SFX_H
