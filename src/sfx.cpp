#include "sfx.h"

   SFX::SFX(const QString& sound_effect)
        : sound_effect(sound_effect) {}

const SFX SFX::COLLECT_1 = SFX(":/sounds/sounds/sound_collect_1");
