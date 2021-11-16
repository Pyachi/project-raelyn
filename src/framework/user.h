#ifndef USER_H
#define USER_H

#include "character.h"
#include "music.h"
#include "uid.h"
#include "util.h"
#include "database_api.h"
#include "scoreboard.h"
#include <QVector>

class User {
  static User* USER;

  User();

  String name;
  String ip;
  UID uid;

  String character;
  Array<int> controls;

  float soundVol;
  float musicVol;

  int currentScore = 0;
  Array<int> highScores;

  QVector<Scoreboard> masterBoard;

 public:
  static void create(void) {
    if (USER != nullptr)
      return;
    USER = new User();
  };

  static const String& getName(void) { return USER->name; }
  static const String& getIP(void) { return USER->ip; }
  static const UID& getUID(void) { return USER->uid; }

  static const String& getCharacter(void) { return USER->character; }
  static void setCharacter(const String& character) {
    USER->character = character;
  }
  static int getKeyUp(void) { return USER->controls[0]; }
  static int getKeyLeft(void) { return USER->controls[1]; }
  static int getKeyDown(void) { return USER->controls[2]; }
  static int getKeyRight(void) { return USER->controls[3]; }
  static int getKeyFocus(void) { return USER->controls[4]; }
  static int getKeyShoot(void) { return USER->controls[5]; }
  static int getKeyBomb(void) { return USER->controls[6]; }
  static const Array<int>& getControls(void) { return USER->controls; }
  static void setControls(const Array<int>& controls) {
    USER->controls = controls;
  }
  static float getSoundVol(void) { return USER->soundVol; }
  static void setSoundVol(float vol) { USER->soundVol = vol; }
  static float getMusicVol(void) { return USER->musicVol; }
  static void setMusicVol(float vol) {
    USER->musicVol = vol;
    Music::changeVolume(vol);
  }
  static int getCurrentScore(void) { return USER->currentScore; }
  static void addCurrentScore(int score) { USER->currentScore += score; }
  static void resetCurrentScore(void) { USER->currentScore = 0; }
  static const Array<int>& getHighScores(void) { return USER->highScores; }
  static void addHighScore(int score) { USER->highScores.push_back(score); }
};

#endif  // USER_H
