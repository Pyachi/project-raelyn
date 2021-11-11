#ifndef MUSIC_H
#define MUSIC_H

#include "util.h"

enum Song {
	SONG_MENU,
	SONG_LVL1,
	SONG_LVL2,
	SONG_LVL3,
	SONG_BOSS1,
	SONG_BOSS2,
	SONG_BOSS3,
	SONG_CREDITS
};

namespace Music {
extern const String get(Song);
extern void playSong(Song);
extern void changeVolume(float);
extern void stopSong(void);
};  // namespace Music

#endif  // MUSIC_H
