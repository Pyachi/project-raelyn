#ifndef CONTROLS_H
#define CONTROLS_H

#include "util.h"

class Controls {
	static Array<Ref<Controls> > list;

	Controls(const String& name, const Array<int>& controls)
			: index(list.size()), controls(controls), name(name) {
		list.push_back(*this);
	}

	Controls(const Controls& controls) = delete;

	const int index;
	const Array<int> controls;

 public:
	const String name;

	operator int() const { return index; }
	operator QString() const { return QString::fromStdString(name); }

	int getKeyUp(void) const { return controls[0]; }
	int getKeyLeft(void) const { return controls[1]; }
	int getKeyDown(void) const { return controls[2]; }
	int getKeyRight(void) const { return controls[3]; }
	int getKeyFocus(void) const { return controls[4]; }
	int getKeyShoot(void) const { return controls[5]; }
	int getKeyBomb(void) const { return controls[6]; }

	static const Controls& valueOf(int i) { return list[i]; }

	static const Controls TRAD;
	static const Controls WASD;
	static const Controls IJKL;
};

#endif  // CONTROLS_H
