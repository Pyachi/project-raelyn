#include "music.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Music {
namespace {
QMediaPlaylist playlist;
QMediaPlayer player;
}

const QString get(Song song) {
	switch (song) {
		case Song::MENU:
			return "qrc:/music/music_menu_theme.ogg";
		case Song::LVL1:
		//      return LVL1;
		case Song::LVL2:
		//      return LVL2;
		case Song::LVL3:
		//      return LVL3;
		case Song::LVL1BOSS:
		//      return LVL1BOSS;
		case Song::LVL2BOSS:
		//      return LVL2BOSS;
		case Song::LVL3BOSS:
		//      return LVL3BOSS;
		case Song::CREDITS:
			//      return CREDITS;
			return "qrc:/music/music_menu_theme.ogg";
	}
}

void playSong(Song song, int volume) {
	playlist.clear();
	playlist.addMedia(QUrl(get(song)));
	playlist.setPlaybackMode(QMediaPlaylist::Loop);
	player.stop();
	player.setPlaylist(&playlist);
	player.setVolume(volume);
	player.play();
}

void stopSong() { player.stop(); }
}  // namespace Music
