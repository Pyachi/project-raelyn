#ifndef USER_H
#define USER_H

#include <QVector>
#include "character.h"
#include "controls.h"
#include "database.h"
#include "music.h"
#include "scoreboard.h"
#include "uid.h"
#include "util.h"

class User {
  static User* USER;

  User();

  String name;
  String ip;
  UID uid;

	const Character* character;
	const Controls* controls;
  int soundVol;
  int musicVol;

  int score = 0;

	Scoreboard masterBoard;
	Scoreboard playerBoard;

 public:
  static void create(void) {
    if (USER != nullptr)
      return;
    USER = new User();
	}

	static const String& getName(void) { return USER->name; }
	static const String& getIP(void) { return USER->ip; }
	static const UID& getUID(void) { return USER->uid; }

	static const Character& getCharacter(void) { return *USER->character; }
	static void setCharacter(const Character& character) {
		USER->character = &character;
		Database::get().updateSettings(getSoundVol(), getMusicVol(), getControls(),
																	 getCharacter());
	}
	static const Controls& getControls(void) { return *USER->controls; }
	static void setControls(const Controls& controls) {
		USER->controls = &controls;
		Database::get().updateSettings(getSoundVol(), getMusicVol(), getControls(),
																	 getCharacter());
	}
	static int getSoundVol(void) { return USER->soundVol; }
	static void setSoundVol(int vol) {
		USER->soundVol = vol;
		Database::get().updateSettings(getSoundVol(), getMusicVol(), getControls(),
																	 getCharacter());
	}
	static int getMusicVol(void) { return USER->musicVol; }
	static void setMusicVol(int vol) {
		USER->musicVol = vol;
		Music::changeVolume(vol);
		Database::get().updateSettings(getSoundVol(), getMusicVol(), getControls(),
																	 getCharacter());
	}
	static int getScore(void) { return USER->score; }
	static void addScore(int score) { USER->score += score; }
	static void resetScore(void) { USER->score = 0; }
	static Scoreboard& getMasterBoard() { return USER->masterBoard; }
	static Scoreboard& getPlayerBoard() { return USER->playerBoard; }

	static void addGame(int score);
	static void addExternalScore(int score, const QString& user);
};

#endif  // USER_H
