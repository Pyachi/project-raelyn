#include "music.h"
#include <QMediaPlayer>

namespace Music {
namespace {
QMediaPlayer player;
}
const QString MENU("qrc:/music/music_menu_theme.ogg");

void playSong(const QString& song, int volume) {
	player.stop();
	player.setMedia(QUrl(song));
	player.setVolume(volume);
	player.play();
}

void stopSong() {
	player.stop();
}
}  // namespace Music
