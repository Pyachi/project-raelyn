#ifndef MUSIC_H
#define MUSIC_H

#include <QString>

enum Song {
	MENU,      // 0
	LVL1,      // 1
	LVL2,      // 2
	LVL3,      // 3
	LVL1BOSS,  // 4
	LVL2BOSS,  // 5
	LVL3BOSS,  // 6
	CREDITS    // 7
};

namespace Music {
extern const QString fromSong(Song);
extern void playSong(Song, int);
extern void stopSong();
};  // namespace Music

#endif  // MUSIC_H
