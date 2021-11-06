#ifndef MUSIC_H
#define MUSIC_H

#include <QString>

namespace Music {
extern const QString MENU;
extern const QString LVL_1;
extern const QString LVL_1_BOSS;
extern const QString LVL_2;
extern const QString LVL_2_BOSS;
extern const QString LVL_3;
extern const QString LVL_3_BOSS;
extern const QString CREDITS;

extern void playSong(const QString&, int);
};

#endif  // MUSIC_H
