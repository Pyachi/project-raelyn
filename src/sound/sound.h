#ifndef SOUND_H
#define SOUND_H

#include <QQueue>
#include <QSoundEffect>

class SFX;
class Song;

class Sound {
 public:
	static void playSound(SFX, qreal);
	static void playMusic(Song);

 private:
	static QQueue<QSoundEffect*>* queue;
	static bool ready;
	static void init();
};

#endif  // SOUND_H
