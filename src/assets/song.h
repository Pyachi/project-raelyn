#ifndef MUSIC_H
#define MUSIC_H

#include <QString>

class Song {
 public:
	static const Song MENU_THEME;
	static const Song LVL_1_THEME;
	static const Song LVL_1_BOSS;
	static const Song LVL_2_THEME;
	static const Song LVL_2_BOSS;
	static const Song LVL_3_THEME;
	static const Song LVL_3_BOSS;

	const QString song_string;

 private:
	Song(const QString&);
};

#endif  // MUSIC_H
