#include "sfx.h"
#include <SFML/Audio.hpp>

Array<Ref<SFX>> SFX::list;
float SFX::volume = 100;
List<sf::Sound*> SFX::players;
bool SFX::init = false;

void SFX::play(float vol) const {
  for (sf::Sound* player : players) {
    if (player->getBuffer() == &buffer &&
        player->getStatus() == sf::Sound::Playing &&
        player->getPlayingOffset().asMilliseconds() < 40)
      return;
  }
  if (!init) {
    for (int i = 0; i < 128; i++)
      players.push_back(new sf::Sound);
    atexit([]() {
      for (sf::Sound* player : players)
        delete player;
    });
    init = true;
  }
  sf::Sound* player = players.front();
  players.pop_front();
  player->stop();
  player->setBuffer(buffer);
  player->setVolume((vol * volume) / 100);
  player->play();
  players.push_back(player);
}

const SFX SFX::COLLECT1("assets/soundeffects/sound_collect_1.wav");
const SFX SFX::COLLECT2("assets/soundeffects/sound_collect_2.wav");
const SFX SFX::COLLECT3("assets/soundeffects/sound_collect_3.wav");
const SFX SFX::EXPL_HEAVY1("assets/soundeffects/sound_expl_heavy_1.wav");
const SFX SFX::EXPL_HEAVY2("assets/soundeffects/sound_expl_heavy_2.wav");
const SFX SFX::EXPL_HEAVY3("assets/soundeffects/sound_expl_heavy_3.wav");
const SFX SFX::EXPL_HEAVY4("assets/soundeffects/sound_expl_heavy_4.wav");
const SFX SFX::EXPL_LIGHT1("assets/soundeffects/sound_expl_light_1.wav");
const SFX SFX::EXPL_LIGHT2("assets/soundeffects/sound_expl_light_2.wav");
const SFX SFX::EXPL_LIGHT3("assets/soundeffects/sound_expl_light_3.wav");
const SFX SFX::EXPL_MED1("assets/soundeffects/sound_expl_med_1.wav");
const SFX SFX::EXPL_MED2("assets/soundeffects/sound_expl_med_2.wav");
const SFX SFX::EXPL_MED3("assets/soundeffects/sound_expl_med_3.wav");
const SFX SFX::EXPL_SUPERHEAVY1(
    "assets/soundeffects/sound_expl_superheavy_1.wav");
const SFX SFX::EXPL_SUPERHEAVY2(
    "assets/soundeffects/sound_expl_superheavy_2.wav");
const SFX SFX::HIT1("assets/soundeffects/sound_hit_1.wav");
const SFX SFX::HIT2("assets/soundeffects/sound_hit_2.wav");
const SFX SFX::HIT3("assets/soundeffects/sound_hit_3.wav");
const SFX SFX::LASER1("assets/soundeffects/sound_laser_1.wav");
const SFX SFX::MISSILE1("assets/soundeffects/sound_missile_1.wav");
const SFX SFX::MISSILE2("assets/soundeffects/sound_missile_2.wav");
const SFX SFX::MISSILE3("assets/soundeffects/sound_missile_3.wav");
const SFX SFX::POWERUP1("assets/soundeffects/sound_powerup_1.wav");
const SFX SFX::POWERUP2("assets/soundeffects/sound_powerup_2.wav");
const SFX SFX::POWERUP3("assets/soundeffects/sound_powerup_3.wav");
const SFX SFX::SELECT1("assets/soundeffects/sound_select_1.wav");
const SFX SFX::SELECT2("assets/soundeffects/sound_select_2.wav");
const SFX SFX::CONNECT("assets/soundeffects/sound_join.wav");
const SFX SFX::DISCONNECT("assets/soundeffects/sound_leave.wav");
// const SFX SFX::ERROR("assets/soundeffects/sound_disconnect.wav");
