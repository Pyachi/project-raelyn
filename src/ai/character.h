#ifndef CHARACTER_H
#define CHARACTER_H

#include "util.h"

class EntityPlayer;
class Texture;
class BulletInfo;
class SFX;

class Character {
  static Array<Ref<Character> > list;

  Character(const String& name,
            const Texture& tex,
						double speed,
						double focusSpeed,
            Func<const List<BulletInfo>(EntityPlayer*)> pattern,
            Func<const SFX&(EntityPlayer*)> shootSound)
      : index(list.size()),
        name(name),
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
  const String name;
  const Texture& tex;
	const double speed;
	const double focusSpeed;
  const Func<const List<BulletInfo>(EntityPlayer*)> pattern;
  const Func<const SFX&(EntityPlayer*)> shootSound;

  operator int() const { return index; }
  operator String() const { return name; }
	operator QString() const { return QString::fromStdString(name); }

  static const Character& valueOf(int i) { return list[i]; }
  static const Array<Ref<Character> >& values() { return list; }

  static const Character PYACHI;
  static const Character AERON;
  static const Character PRYSMA;
  static const Character ANEKHANDA;
};

#endif  // CHARACTER_H
