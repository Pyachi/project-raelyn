#include "sfx.h"
#include <QSoundEffect>
#include "util.h"

namespace SFX {
namespace {
List<QSoundEffect*> queue;
bool queueSetup = false;
}  // namespace
double volume = 1;

const QString get(SoundEffect sfx) {
	switch (sfx) {
		case COLLECT_1:
			return "qrc:/soundeffects/sound_collect_1.wav";
		case COLLECT_2:
			return "qrc:/soundeffects/sound_collect_2.wav";
		case COLLECT_3:
			return "qrc:/soundeffects/sound_collect_3.wav";
		case EXPL_HEAVY_1:
			return "qrc:/soundeffects/sound_expl_heavy_1.wav";
		case EXPL_HEAVY_2:
			return "qrc:/soundeffects/sound_expl_heavy_2.wav";
		case EXPL_HEAVY_3:
			return "qrc:/soundeffects/sound_expl_heavy_3.wav";
		case EXPL_HEAVY_4:
			return "qrc:/soundeffects/sound_expl_heavy_4.wav";
		case EXPL_LIGHT_1:
			return "qrc:/soundeffects/sound_expl_light_1.wav";
		case EXPL_LIGHT_2:
			return "qrc:/soundeffects/sound_expl_light_2.wav";
		case EXPL_LIGHT_3:
			return "qrc:/soundeffects/sound_expl_light_3.wav";
		case EXPL_MED_1:
			return "qrc:/soundeffects/sound_expl_med_1.wav";
		case EXPL_MED_2:
			return "qrc:/soundeffects/sound_expl_med_2.wav";
		case EXPL_MED_3:
			return "qrc:/soundeffects/sound_expl_med_3.wav";
		case EXPL_SUPERHEAVY_1:
			return "qrc:/soundeffects/sound_expl_superheavy_1.wav";
		case EXPL_SUPERHEAVY_2:
			return "qrc:/soundeffects/sound_expl_superheavy_2.wav";
		case HIT_1:
			return "qrc:/soundeffects/sound_hit_1.wav";
		case HIT_2:
			return "qrc:/soundeffects/sound_hit_2.wav";
		case HIT_3:
			return "qrc:/soundeffects/sound_hit_3.wav";
		case LASER_1:
			return "qrc:/soundeffects/sound_laser_1.wav";
		case MISSILE_1:
			return "qrc:/soundeffects/sound_missile_1.wav";
		case MISSILE_2:
			return "qrc:/soundeffects/sound_missile_2.wav";
		case MISSILE_3:
			return "qrc:/soundeffects/sound_missile_3.wav";
		case POWERUP_1:
			return "qrc:/soundeffects/sound_powerup_1.wav";
		case POWERUP_2:
			return "qrc:/soundeffects/sound_powerup_2.wav";
		case POWERUP_3:
			return "qrc:/soundeffects/sound_powerup_3.wav";
		case SELECT_1:
			return "qrc:/soundeffects/sound_select_1.wav";
		case SELECT_2:
			return "qrc:/soundeffects/sound_select_2.wav";
	}
}

void playSound(SoundEffect sfx, double vol) {
	if (!queueSetup) {
		for (int i = 0; i < 32; i++)
			queue.push_back(new QSoundEffect);
		queueSetup = true;
	}
	QSoundEffect* player = queue.front();
	queue.pop_front();
	player->stop();
	player->setSource(get(sfx));
	player->setVolume(volume * vol);
	player->play();
	queue.push_back(player);
}
}  // namespace SFX
