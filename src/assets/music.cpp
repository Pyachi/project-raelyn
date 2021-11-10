#include "music.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Music {
namespace {
QMediaPlaylist* playlist;
QMediaPlayer* player;
bool init = false;
int volume = 100;
}  // namespace

const QString get(Song song) {
	switch (song) {
		case SONG_MENU:
			return "qrc:/music/music_menu_theme.ogg";
		case SONG_LVL1:
			return "qrc:/music/music_menu_theme.ogg";
		case SONG_LVL2:
			return "qrc:/music/music_lvl2_theme.ogg";
		case SONG_LVL3:
			return "qrc:/music/music_menu_theme.ogg";
		case SONG_BOSS1:
			return "qrc:/music/music_lvl1_boss.ogg";
		case SONG_BOSS2:
			return "qrc:/music/music_lvl2_boss.ogg";
		case SONG_BOSS3:
			return "qrc:/music/music_menu_theme.ogg";
		case SONG_CREDITS:
			return "qrc:/music/music_menu_theme.ogg";
	}
}

void playSong(Song song) {
	if (!init) {
		playlist = new QMediaPlaylist;
		player = new QMediaPlayer;
		init = true;
	}
	playlist->clear();
	playlist->addMedia(QUrl(get(song)));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	player->stop();
	player->setPlaylist(playlist);
	player->setVolume(volume);
	player->play();
}

void changeVolume(int vol) {
	volume = vol;
	player->setVolume(volume);
}

void stopSong(void) { player->stop(); }
}  // namespace Music
