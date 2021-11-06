#include "sfx.h"
#include <QQueue>
#include <QSoundEffect>

namespace SFX {
const QString COLLECT_1("qrc:/QStrings/QString_collect_1.wav");
const QString COLLECT_2("qrc:/QStrings/QString_collect_2.wav");
const QString COLLECT_3("qrc:/QStrings/QString_collect_3.wav");
const QString EXPL_HEAVY_1("qrc:/QStrings/QString_expl_heavy_1.wav");
const QString EXPL_HEAVY_2("qrc:/QStrings/QString_expl_heavy_2.wav");
const QString EXPL_HEAVY_3("qrc:/QStrings/QString_expl_heavy_3.wav");
const QString EXPL_HEAVY_4("qrc:/QStrings/QString_epl_heavy_4.wav");
const QString EXPL_LIGHT_1("qrc:/QStrings/QString_expl_light_1.wav");
const QString EXPL_LIGHT_2("qrc:/QStrings/QString_expl_light_2.wav");
const QString EXPL_LIGHT_3("qrc:/QStrings/QString_expl_light_3.wav");
const QString EXPL_MED_1("qrc:/QStrings/QString_expl_med_1.wav");
const QString EXPL_MED_2("qrc:/QStrings/QString_expl_med_2.wav");
const QString EXPL_MED_3("qrc:/QStrings/QString_expl_med_3.wav");
const QString EXPL_SUPERHEAVY_1("qrc:/QStrings/QString_expl_superheavy_1.wav");
const QString EXPL_SUPERHEAVY_2("qrc:/QStrings/QString_expl_superheavy_2.wav");
const QString HIT_1("qrc:/QStrings/QString_hit_1.wav");
const QString HIT_2("qrc:/QStrings/QString_hit_2.wav");
const QString HIT_3("qrc:/QStrings/QString_hit_3.wav");
const QString LASER_1("qrc:/QStrings/QString_laser_1.wav");
const QString MISSILE_1("qrc:/QStrings/QString_missile_1.wav");
const QString MISSILE_2("qrc:/QStrings/QString_missile_2.wav");
const QString MISSILE_3("qrc:/QStrings/QString_missile_3.wav");
const QString POWERUP_1("qrc:/QStrings/QString_powerup_1.wav");
const QString POWERUP_2("qrc:/QStrings/QString_powerup_2.wav");
const QString POWERUP_3("qrc:/QStrings/QString_powerup_3.wav");
const QString SELECT_1("qrc:/QStrings/QString_select_1.wav");
const QString SELECT_2("qrc:/QStrings/QString_select_2.wav");

void playSound(const QString& sound, qreal volume) {
	QSoundEffect player;
	player.setSource(sound);
	player.setVolume(volume);
	player.play();
}
}
