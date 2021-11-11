#include "music.h"
#include <SFML/Audio.hpp>

namespace Music {
namespace {
sf::Music* player;
bool setup = false;
int volume = 100;
}  // namespace

const String get(Song song) {
	switch (song) {
		case SONG_MENU:
			return "assets/music/music_menu_theme.ogg";
		case SONG_LVL1:
			return "assets/music/music_menu_theme.ogg";
		case SONG_LVL2:
			return "assets/music/music_lvl2_theme.ogg";
		case SONG_LVL3:
			return "assets/music/music_menu_theme.ogg";
		case SONG_BOSS1:
			return "assets/music/music_lvl1_boss.ogg";
		case SONG_BOSS2:
			return "assets/music/music_lvl2_boss.ogg";
		case SONG_BOSS3:
			return "assets/music/music_menu_theme.ogg";
		case SONG_CREDITS:
			return "assets/music/music_menu_theme.ogg";
	}
}

void playSong(Song song) {
	if (!setup) {
		player = new sf::Music;
		atexit([]() { delete player; });
		setup = true;
	}
	player->stop();
	player->openFromFile(get(song));
	player->setVolume(volume);
	player->play();
}

void changeVolume(int vol) {
	volume = vol;
	player->setVolume(volume);
}

void stopSong(void) {
	player->stop();
}
}  // namespace Music
