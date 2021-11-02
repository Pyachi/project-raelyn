#include "sound.h"
#include "sfx.h"
#include <QMediaPlayer>

void Sound::playSound(SFX effect) {
	QMediaPlayer* sound = new QMediaPlayer;
	sound->setMedia(QUrl(effect.sound_effect));
	sound->play();
}

//void Sound::playMusic(Song song) {
//	QMediaPlayer* sound = new QMediaPlayer;
//	sound->setMedia(QUrl(song.sound_effect));
//	sound->play();
//}

void Sound::stopSound() {

}
