#include "sfx.h"
#include <QSound>
#include <QSoundEffect>
#include "util.h"

namespace SFX {
namespace {
List<QSoundEffect*> queue;
bool queueSetup = false;
}  // namespace
double volume = 1;

const QString get(Sound sfx) {
  switch (sfx) {
    case SFX_COLLECT1:
      return "qrc:/soundeffects/sound_collect_1.wav";
    case SFX_COLLECT2:
      return "qrc:/soundeffects/sound_collect_2.wav";
    case SFX_COLLECT3:
      return "qrc:/soundeffects/sound_collect_3.wav";
    case SFX_EXPL_HEAVY1:
      return "qrc:/soundeffects/sound_expl_heavy_1.wav";
    case SFX_EXPL_HEAVY2:
      return "qrc:/soundeffects/sound_expl_heavy_2.wav";
    case SFX_EXPL_HEAVY3:
      return "qrc:/soundeffects/sound_expl_heavy_3.wav";
    case SFX_EXPL_HEAVY4:
      return "qrc:/soundeffects/sound_expl_heavy_4.wav";
    case SFX_EXPL_LIGHT1:
      return "qrc:/soundeffects/sound_expl_light_1.wav";
    case SFX_EXPL_LIGHT2:
      return "qrc:/soundeffects/sound_expl_light_2.wav";
    case SFX_EXPL_LIGHT3:
      return "qrc:/soundeffects/sound_expl_light_3.wav";
    case SFX_EXPL_MED1:
      return "qrc:/soundeffects/sound_expl_med_1.wav";
    case SFX_EXPL_MED2:
      return "qrc:/soundeffects/sound_expl_med_2.wav";
    case SFX_EXPL_MED3:
      return "qrc:/soundeffects/sound_expl_med_3.wav";
    case SFX_EXPL_SUPERHEAVY1:
      return "qrc:/soundeffects/sound_expl_superheavy_1.wav";
    case SFX_EXPL_SUPERHEAVY2:
      return "qrc:/soundeffects/sound_expl_superheavy_2.wav";
    case SFX_HIT1:
      return "qrc:/soundeffects/sound_hit_1.wav";
    case SFX_HIT2:
      return "qrc:/soundeffects/sound_hit_2.wav";
    case SFX_HIT3:
      return "qrc:/soundeffects/sound_hit_3.wav";
    case SFX_LASER1:
      return "qrc:/soundeffects/sound_laser_1.wav";
    case SFX_MISSILE1:
      return "qrc:/soundeffects/sound_missile_1.wav";
    case SFX_MISSILE2:
      return "qrc:/soundeffects/sound_missile_2.wav";
    case SFX_MISSILE3:
      return "qrc:/soundeffects/sound_missile_3.wav";
    case SFX_POWERUP1:
      return "qrc:/soundeffects/sound_powerup_1.wav";
    case SFX_POWERUP2:
      return "qrc:/soundeffects/sound_powerup_2.wav";
    case SFX_POWERUP3:
      return "qrc:/soundeffects/sound_powerup_3.wav";
    case SFX_SELECT1:
      return "qrc:/soundeffects/sound_select_1.wav";
    case SFX_SELECT2:
      return "qrc:/soundeffects/sound_select_2.wav";
    case SFX_CONNECT:
      return "qrc:/soundeffects/sound_join.wav";
    case SFX_DISCONNECT:
      return "qrc:/soundeffects/sound_leave.wav";
    case SFX_ERROR:
      return "qrc:/soundeffects/sound_disconnect.wav";
  }
}

void playSound(Sound sfx, double vol) {
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
