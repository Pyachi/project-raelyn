#include <QSoundEffect>
#include <QMediaPlayer>
#include "sfx.h"
#include "sound.h"
#include "song.h"

QQueue<QSoundEffect*>* Sound::queue = nullptr;
QMediaPlayer* Sound::global_song = nullptr;

void Sound::playSound(const SFX& effect, qreal vol) {
	if (queue == nullptr) {
		queue = new QQueue<QSoundEffect*>;
		for (int i = 0; i < 31; i++)
			queue->enqueue(new QSoundEffect);
	}

	QSoundEffect* player = queue->dequeue();
	player->stop();
	player->setSource(QUrl(effect.sound_effect));
	player->setVolume(vol);
	player->play();
	queue->enqueue(player);
}

void Sound::playMusic(const Song& song, int volume) {
	if (global_song == nullptr)
		global_song = new QMediaPlayer;

	global_song->stop();
	global_song->setMedia(QUrl("qrc:/sounds/sounds/music_menu_theme.ogg"));
	global_song->setVolume(100);
	global_song->play();
}

void Sound::pauseMusic() { global_song->pause(); }
