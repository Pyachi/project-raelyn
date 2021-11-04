#ifndef SOUND_H
#define SOUND_H

#include <QQueue>
#include <QSoundEffect>
#include <QMediaPlayer>

class SFX;
class Song;

class Sound {
 public:
	static void playSound(SFX, qreal);
    static void playMusic(Song, int);

 private:
    static QMediaPlayer *global_song;
	static QQueue<QSoundEffect*>* queue;
	static bool ready;
	static void init();
};

#endif  // SOUND_H
