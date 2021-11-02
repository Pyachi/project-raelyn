#include "sound.h"
#include "sfx.h"

QSet<QMediaPlayer*>* Sound::sounds = new QSet<QMediaPlayer*>();

void Sound::playSound(SFX effect) {
	QSet<QMediaPlayer*> set = QSet<QMediaPlayer*>(*sounds);
	foreach(QMediaPlayer * player, set) {
		if (player->state() == QMediaPlayer::StoppedState)
			sounds->remove(player);
	}

	QMediaPlayer* player = new QMediaPlayer;
	player->setMedia(QUrl(effect.sound_effect));
	player->play();
	sounds->insert(player);
}

void Sound::stopSound() {
	foreach(QMediaPlayer * player, *sounds) { player->stop(); }
	sounds->clear();
}

void Sound::stopSound(SFX effect) {
	QSet<QMediaPlayer*> set = QSet<QMediaPlayer*>(*sounds);
	foreach(QMediaPlayer * player, set) {
		if (player->media().canonicalUrl().path() == effect.sound_effect) {
			player->stop();
			sounds->remove(player);
		}
	}
}
