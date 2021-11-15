#ifndef MUSIC_H
#define MUSIC_H

#include <SFML/Audio.hpp>
#include "util.h"

class Music {
	static Array<Ref<Music> > list;
  static float volume;
  static sf::Music player;

  Music(const String& file) : index(list.size()), file(file) {
    list.push_back(*this);
  }

  Music(const Music& song) = delete;

  const int index;
  const String file;

 public:
  void play() const;

	operator int() const { return index; }

	static void changeVolume(float vol) {
		volume = vol;
		player.setVolume(vol);
	}
	static void stop() { player.stop(); }

  static const Music& valueOf(int i) { return list[i]; }

  static const Music MENU;
  static const Music LVL1;
  static const Music LVL2;
  static const Music LVL3;
  static const Music BOSS1;
  static const Music BOSS2;
  static const Music BOSS3;
  static const Music LOSS;
  static const Music END;
};

#endif  // MUSIC_H
