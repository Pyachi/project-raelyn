#ifndef FONT_H
#define FONT_H

#include "util.h"
#include <QFont>
#include <QFontDatabase>

class Font {
	static Map<String, int> fonts;

	Font(const String& file) : file(file) {}

	Font(const Font& font) = delete;

	const String file;

 public:
	operator QFont() const {
		int id;
		if (fonts.count(file))
			id = fonts.at(file);
		else {
			id = QFontDatabase::addApplicationFont(QString::fromStdString(file));
			fonts.insert({file, id});
		}
		return {QString::fromStdString(
				QFontDatabase::applicationFontFamilies(id).at(0).toStdString())};
	}

	static const Font PRESSSTART;
};

#endif  // FONT_H
