#include "song.h"

Song::Song(const QString& song_string) : song_string(song_string) {}

const Song Song::MENU_THEME = Song("qrc:/sounds/sounds/music_menu_theme.ogg");
