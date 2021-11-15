#ifndef CHARACTER_H
#define CHARACTER_H

#include "util.h"

class EntityPlayer;
class Texture;
class BulletInfo;
class SFX;

class Character {
	static Array<Ref<Character> > list;

  Character(const Texture& tex,
            int speed,
            int focusSpeed,
						Func<const List<BulletInfo>(EntityPlayer*)> pattern,
						Func<const SFX&(EntityPlayer*)> shootSound)
      : index(list.size()),
        tex(tex),
        speed(speed),
        focusSpeed(focusSpeed),
				pattern(pattern),
				shootSound(shootSound) {
    list.push_back(*this);
  }

  Character(const Character& player) = delete;

  const int index;

 public:
  const Texture& tex;
  const int speed;
  const int focusSpeed;
  const Func<const List<BulletInfo>(EntityPlayer*)> pattern;
	const Func<const SFX&(EntityPlayer*)> shootSound;

	operator int() const { return index; }

  static const Character& valueOf(int i) { return list[i]; }
	static const Array<Ref<Character> >& values() { return list; }

  static const Character PYACHI;
  static const Character AERON;
  static const Character PRYSMA;
  static const Character ANEKHANDA;
};

#endif  // CHARACTER_H
