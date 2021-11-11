#include "sfx.h"
#include <SFML/Audio.hpp>
#include "util.h"

namespace SFX {
namespace {
Map<String, sf::SoundBuffer*> buffers;
List<sf::Sound*> players;
bool setup = false;
}  // namespace
float volume = 1;

const String get(Sound sfx) {
  switch (sfx) {
    case SFX_COLLECT1:
			return "assets/soundeffects/sound_collect_1.wav";
    case SFX_COLLECT2:
			return "assets/soundeffects/sound_collect_2.wav";
    case SFX_COLLECT3:
			return "assets/soundeffects/sound_collect_3.wav";
    case SFX_EXPL_HEAVY1:
			return "assets/soundeffects/sound_expl_heavy_1.wav";
    case SFX_EXPL_HEAVY2:
			return "assets/soundeffects/sound_expl_heavy_2.wav";
    case SFX_EXPL_HEAVY3:
			return "assets/soundeffects/sound_expl_heavy_3.wav";
    case SFX_EXPL_HEAVY4:
			return "assets/soundeffects/sound_expl_heavy_4.wav";
    case SFX_EXPL_LIGHT1:
			return "assets/soundeffects/sound_expl_light_1.wav";
    case SFX_EXPL_LIGHT2:
			return "assets/soundeffects/sound_expl_light_2.wav";
    case SFX_EXPL_LIGHT3:
			return "assets/soundeffects/sound_expl_light_3.wav";
    case SFX_EXPL_MED1:
			return "assets/soundeffects/sound_expl_med_1.wav";
    case SFX_EXPL_MED2:
			return "assets/soundeffects/sound_expl_med_2.wav";
    case SFX_EXPL_MED3:
			return "assets/soundeffects/sound_expl_med_3.wav";
    case SFX_EXPL_SUPERHEAVY1:
			return "assets/soundeffects/sound_expl_superheavy_1.wav";
    case SFX_EXPL_SUPERHEAVY2:
			return "assets/soundeffects/sound_expl_superheavy_2.wav";
    case SFX_HIT1:
			return "assets/soundeffects/sound_hit_1.wav";
    case SFX_HIT2:
			return "assets/soundeffects/sound_hit_2.wav";
    case SFX_HIT3:
			return "assets/soundeffects/sound_hit_3.wav";
    case SFX_LASER1:
			return "assets/soundeffects/sound_laser_1.wav";
    case SFX_MISSILE1:
			return "assets/soundeffects/sound_missile_1.wav";
    case SFX_MISSILE2:
			return "assets/soundeffects/sound_missile_2.wav";
    case SFX_MISSILE3:
			return "assets/soundeffects/sound_missile_3.wav";
    case SFX_POWERUP1:
			return "assets/soundeffects/sound_powerup_1.wav";
    case SFX_POWERUP2:
			return "assets/soundeffects/sound_powerup_2.wav";
    case SFX_POWERUP3:
			return "assets/soundeffects/sound_powerup_3.wav";
    case SFX_SELECT1:
			return "assets/soundeffects/sound_select_1.wav";
    case SFX_SELECT2:
			return "assets/soundeffects/sound_select_2.wav";
    case SFX_CONNECT:
			return "assets/soundeffects/sound_join.wav";
    case SFX_DISCONNECT:
			return "assets/soundeffects/sound_leave.wav";
    case SFX_ERROR:
			return "assets/soundeffects/sound_disconnect.wav";
  }
}

void playSound(Sound sfx, float vol) {
	if (!buffers.count(get(sfx))) {
		sf::SoundBuffer* buffer = new sf::SoundBuffer;
		buffer->loadFromFile(get(sfx));
		buffers.insert({get(sfx), buffer});
	}
	if (!setup) {
		for (int i = 0; i < 32; i++)
			players.push_back(new sf::Sound);
		atexit([]() {
			for (auto player : players)
				delete player;
			for (auto buffer : buffers)
				delete buffer.second;
		});
		setup = true;
	}
	sf::SoundBuffer* buffer = buffers[get(sfx)];
	sf::Sound* player = players.front();
	players.pop_front();
	player->stop();
	player->setBuffer(*buffer);
	player->setVolume(volume * vol);
	player->play();
	players.push_back(player);
}
}  // namespace SFX
