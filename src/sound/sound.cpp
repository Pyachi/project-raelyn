#include "sound.h"
#include <QMediaPlayer>
#include "sfx.h"

void Sound::playSound(SFX effect) {
	QMediaPlayer* sound = new QMediaPlayer;
	sound->setMedia(QUrl(effect.sound_effect));
	sound->play();
}

// void Sound::playMusic(Song song) {
//	QMediaPlayer* sound = new QMediaPlayer;
//	sound->setMedia(QUrl(song.sound_effect));
//	sound->play();
//}

void Sound::stopSound() {}
