#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "sfx.h"
#include "sound.h"
#include "song.h"

QQueue<QSoundEffect*>* Sound::queue = nullptr;
QMediaPlayer* Sound::global_song = nullptr;
QMediaPlaylist* Sound::song_loop_playlist = nullptr;

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

    if(song_loop_playlist == nullptr)
        song_loop_playlist = new QMediaPlaylist;

    song_loop_playlist->clear();

    song_loop_playlist->addMedia(QUrl(song.song_string));

    global_song->setPlaylist(song_loop_playlist);
	global_song->setVolume(100);

    global_song->play();
}

void Sound::pauseMusic() { global_song->pause(); }

void Sound::setLoopMusic()
{
    song_loop_playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

void Sound::resetLoopMusic()
{
    song_loop_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}
