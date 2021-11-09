#ifndef MUSIC_H
#define MUSIC_H

#include <QString>

enum Song { MENU, LVL1, LVL2, LVL3, LVL1BOSS, LVL2BOSS, LVL3BOSS, CREDITS };

namespace Music {
extern const QString get(Song);
extern void playSong(Song);
extern void changeVolume(int);
extern void stopSong();
};  // namespace Music

#endif  // MUSIC_H
