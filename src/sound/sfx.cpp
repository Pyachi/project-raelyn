#include "sfx.h"

SFX::SFX(const QString& sound_effect) : sound_effect(sound_effect) {}

const SFX SFX::COLLECT_1 = SFX("qrc:/sounds/sounds/sound_collect_1.ogg");
const SFX SFX::EXPL_SUPERHEAVY_2 =
		SFX("qrc:/sounds/sounds/sound_expl_superheavy_2.ogg");
const SFX SFX::HIT_1 = SFX("qrc:/sounds/sounds/sound_hit_1.ogg");
