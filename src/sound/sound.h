#ifndef SOUND_H
#define SOUND_H

class SFX;
class Song;

class Sound {
 public:
	static void playSound(SFX);
	static void playMusic(Song);
	static void stopSound();
};

#endif  // SOUND_H
