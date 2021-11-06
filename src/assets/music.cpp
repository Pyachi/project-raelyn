#include "music.h"
#include <QMediaPlayer>
#include <QSound>
#include <QSoundEffect>

namespace Music {
namespace {
QMediaPlayer player;
}
const QString MENU = "qrc:/music/music_menu_theme.ogg";

void playSong(const QString& song, int volume) {
	player.stop();
	player.setMedia(QUrl(song));
	player.setVolume(volume);
	player.play();
}
}
