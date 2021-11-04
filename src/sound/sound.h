#ifndef SOUND_H
#define SOUND_H

#include <QQueue>
#include <QSoundEffect>
#include <QMediaPlayer>

class SFX;
class Song;

class Sound {
 public:
	static void playSound(const SFX&, qreal);
	static void playMusic(const Song&, int);
    static void pauseMusic();
    static void setLoopMusic();
    static void resetLoopMusic();

 private:
  static QMediaPlayer* global_song;
  static QMediaPlaylist* song_loop_playlist;
  static QQueue<QSoundEffect*>* queue;
};

#endif  // SOUND_H
