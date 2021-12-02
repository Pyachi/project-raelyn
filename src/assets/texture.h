#ifndef TEXTURES_H
#define TEXTURES_H

#include <QPixmap>
#include "util.h"

class Texture {
	static Array<Ref<Texture> > list;

  Texture(const String& file, int zValue)
      : index(list.size()), file(file), zValue(zValue) {
    list.push_back(*this);
  }

  Texture(const Texture& texture) = delete;

	const int index;
	const String file;

 public:
  const int zValue;

  operator const QPixmap() const {
    return QPixmap(QString::fromStdString(file));
	};

	static const Texture& valueOf(int i) { return list[i]; }
	static const Array<Ref<Texture> >& values() { return list; }

  //***************************************************************************
  // Round Bullets
  static const Texture ROUNDRED;
  static const Texture ROUNDORANGE;
  static const Texture ROUNDYELLOW;
  static const Texture ROUNDGREEN;
  static const Texture ROUNDAQUA;
  static const Texture ROUNDBLUE;
  static const Texture ROUNDPURPLE;
  static const Texture ROUNDMAGENTA;
  //***************************************************************************
  // Elliptical Bullets
  static const Texture ELLIPSERED;
  static const Texture ELLIPSEORANGE;
  static const Texture ELLIPSEYELLOW;
  static const Texture ELLIPSEGREEN;
  static const Texture ELLIPSEAQUA;
  static const Texture ELLIPSEBLUE;
  static const Texture ELLIPSEPURPLE;
  static const Texture ELLIPSEMAGENTA;
  //***************************************************************************
  // Arrowhead Bullets
  static const Texture ARROWRED;
  static const Texture ARROWORANGE;
  static const Texture ARROWYELLOW;
  static const Texture ARROWGREEN;
  static const Texture ARROWAQUA;
  static const Texture ARROWBLUE;
  static const Texture ARROWPURPLE;
  static const Texture ARROWMAGENTA;
  //***************************************************************************
  // Star Bullets
  static const Texture STARRED;
  static const Texture STARORANGE;
  static const Texture STARYELLOW;
  static const Texture STARGREEN;
  static const Texture STARAQUA;
  static const Texture STARBLUE;
  static const Texture STARPURPLE;
  static const Texture STARMAGENTA;
  //***************************************************************************
  // Lazer Bullets
  static const Texture LAZERRED;
  static const Texture LAZERORANGE;
  static const Texture LAZERYELLOW;
  static const Texture LAZERGREEN;
  static const Texture LAZERAQUA;
  static const Texture LAZERBLUE;
  static const Texture LAZERPURPLE;
  static const Texture LAZERMAGENTA;
  //***************************************************************************
  // Collectables
  static const Texture POWER;
  static const Texture POINTS;
	static const Texture HEALTH;
	static const Texture BOMB;
  //***************************************************************************
  // Temporary
  static const Texture ENEMY;
  static const Texture SCREEN;
  static const Texture TITLE;
  static const Texture BACKGROUND;
  static const Texture BACKGROUND2;
	static const Texture ICON;
  //***************************************************************************
  // Players
  static const Texture PYACHI;
  static const Texture AERON;
  static const Texture PRYSMA;
  static const Texture ANEKHANDA;
  static const Texture HITBOX;
	//***************************************************************************
	// Sidebar
	static const Texture S_HEALTH;
	static const Texture S_HEALTH_D;
	static const Texture S_BOMB;
	static const Texture S_BOMB_D;
};

#endif  // TEXTURES_H
