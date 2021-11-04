#include <QSoundEffect>
#include <QMediaPlayer>
#include "sfx.h"
#include "sound.h"
#include "song.h"

QQueue<QSoundEffect*>* Sound::queue = new QQueue<QSoundEffect*>;
QMediaPlayer *global_song = new QMediaPlayer;

bool Sound::ready = false;

void Sound::playSound(SFX effect, qreal vol) {
	if (!ready)
		init();

	QSoundEffect* player = queue->dequeue();
	player->setSource(QUrl(effect.sound_effect));
	player->setVolume(vol);
	player->play();
	queue->enqueue(player);
}

void Sound::playMusic(Song song, int volume)
{
    if(global_song->state() != QMediaPlayer::StoppedState)
    {
        global_song->stop();
        global_song->setMedia(QUrl(song.song_string));
        global_song->setVolume(volume);
        global_song->play();
    }else {
        global_song->setMedia(QUrl(song.song_string));
        global_song->setVolume(volume);
        global_song->play();
    }
}

void Sound::init() {
	for (int i = 0; i < 32; i++)
		queue->enqueue(new QSoundEffect);
	ready = true;
}
