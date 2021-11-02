#ifndef SOUND_H
#define SOUND_H

#include <QSet>
#include <QMediaPlayer>

class SFX;
class Song;

class Sound {
 public:
	static void playSound(SFX);
	static void playMusic(Song);
	static void stopSound();
	static void stopSound(SFX);
	static void stopSound(Song);

 private:
	static QSet<QMediaPlayer*>* sounds;
};

#endif  // SOUND_H
