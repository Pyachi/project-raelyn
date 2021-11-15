#ifndef SFX_H
#define SFX_H

#include <SFML/Audio.hpp>
#include "util.h"

class SFX {
	static Array<Ref<SFX> > list;
  static float volume;
  static List<sf::Sound*> players;
  static bool init;

  SFX(const String& file) : index(list.size()), buffer() {
    list.push_back(*this);
    buffer.loadFromFile(file);
  }

  SFX(const SFX& sfx) = delete;

  const int index;
  sf::SoundBuffer buffer;

 public:
  void play(float vol = 100) const;

	operator int() const { return index; }

	static float getVolume() { return volume; }
  static void changeVolume(float vol) { volume = vol; }

  static const SFX& valueOf(int i) { return list[i]; }

  static const SFX COLLECT1;
  static const SFX COLLECT2;
  static const SFX COLLECT3;
  static const SFX EXPL_HEAVY1;
  static const SFX EXPL_HEAVY2;
  static const SFX EXPL_HEAVY3;
  static const SFX EXPL_HEAVY4;
  static const SFX EXPL_LIGHT1;
  static const SFX EXPL_LIGHT2;
  static const SFX EXPL_LIGHT3;
  static const SFX EXPL_MED1;
  static const SFX EXPL_MED2;
  static const SFX EXPL_MED3;
  static const SFX EXPL_SUPERHEAVY1;
  static const SFX EXPL_SUPERHEAVY2;
  static const SFX HIT1;
  static const SFX HIT2;
  static const SFX HIT3;
  static const SFX LASER1;
  static const SFX MISSILE1;
  static const SFX MISSILE2;
  static const SFX MISSILE3;
  static const SFX POWERUP1;
  static const SFX POWERUP2;
  static const SFX POWERUP3;
  static const SFX SELECT1;
  static const SFX SELECT2;
  static const SFX CONNECT;
  static const SFX DISCONNECT;
  //  static const SFX ERROR;
};

#endif  // SFX_H
