#include "sound.h"
#include <QSoundEffect>
#include "sfx.h"

QQueue<QSoundEffect*>* Sound::queue = new QQueue<QSoundEffect*>;

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

void Sound::init() {
	for (int i = 0; i < 32; i++)
		queue->enqueue(new QSoundEffect);
	ready = true;
}
