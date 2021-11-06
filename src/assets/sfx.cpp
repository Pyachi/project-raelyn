#include "sfx.h"
#include <QSoundEffect>
#include <queue>

namespace SFX {
namespace {
std::queue<QSoundEffect*> queue;
bool queueSetup = false;
}  // namespace
const QString COLLECT_1("qrc:/soundeffects/sound_collect_1.wav");
const QString COLLECT_2("qrc:/soundeffects/sound_collect_2.wav");
const QString COLLECT_3("qrc:/soundeffects/sound_collect_3.wav");
const QString EXPL_HEAVY_1("qrc:/soundeffects/sound_expl_heavy_1.wav");
const QString EXPL_HEAVY_2("qrc:/soundeffects/sound_expl_heavy_2.wav");
const QString EXPL_HEAVY_3("qrc:/soundeffects/sound_expl_heavy_3.wav");
const QString EXPL_HEAVY_4("qrc:/soundeffects/sound_epl_heavy_4.wav");
const QString EXPL_LIGHT_1("qrc:/soundeffects/sound_expl_light_1.wav");
const QString EXPL_LIGHT_2("qrc:/soundeffects/sound_expl_light_2.wav");
const QString EXPL_LIGHT_3("qrc:/soundeffects/sound_expl_light_3.wav");
const QString EXPL_MED_1("qrc:/soundeffects/sound_expl_med_1.wav");
const QString EXPL_MED_2("qrc:/soundeffects/sound_expl_med_2.wav");
const QString EXPL_MED_3("qrc:/soundeffects/sound_expl_med_3.wav");
const QString EXPL_SUPERHEAVY_1(
    "qrc:/soundeffects/sound_expl_superheavy_1.wav");
const QString EXPL_SUPERHEAVY_2(
    "qrc:/soundeffects/sound_expl_superheavy_2.wav");
const QString HIT_1("qrc:/soundeffects/sound_hit_1.wav");
const QString HIT_2("qrc:/soundeffects/sound_hit_2.wav");
const QString HIT_3("qrc:/soundeffects/sound_hit_3.wav");
const QString LASER_1("qrc:/soundeffects/sound_laser_1.wav");
const QString MISSILE_1("qrc:/soundeffects/sound_missile_1.wav");
const QString MISSILE_2("qrc:/soundeffects/sound_missile_2.wav");
const QString MISSILE_3("qrc:/soundeffects/sound_missile_3.wav");
const QString POWERUP_1("qrc:/soundeffects/sound_powerup_1.wav");
const QString POWERUP_2("qrc:/soundeffects/sound_powerup_2.wav");
const QString POWERUP_3("qrc:/soundeffects/sound_powerup_3.wav");
const QString SELECT_1("qrc:/soundeffects/sound_select_1.wav");
const QString SELECT_2("qrc:/soundeffects/sound_select_2.wav");

void playSound(const QString& sound, qreal volume) {
  if (!queueSetup) {
    for (int i = 0; i < 64; i++)
      queue.push(new QSoundEffect);
    queueSetup = true;
  }

  QSoundEffect* player = queue.front();
  player->setSource(sound);
  player->setVolume(volume);
  player->play();
  queue.push(player);
  queue.pop();
}
}  // namespace SFX
