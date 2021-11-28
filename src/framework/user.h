#ifndef USER_H
#define USER_H

#include <QVector>
#include "character.h"
#include "controls.h"
#include "database_api.h"
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

  Scoreboard* masterBoard;
  Scoreboard* playerBoard;

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
    }
    static const Controls& getControls(void) { return *USER->controls; }
    static void setControls(const Controls& controls) {
        USER->controls = &controls;
    }
    static int getSoundVol(void) { return USER->soundVol; }
    static void setSoundVol(int vol) { USER->soundVol = vol; }
    static int getMusicVol(void) { return USER->musicVol; }
    static void setMusicVol(int vol) {
        USER->musicVol = vol;
        Music::changeVolume(vol);
    }
    static int getScore(void) { return USER->score; }
    static void addScore(int score) { USER->score += score; }
    static void resetScore(void) { USER->score = 0; }
        //  static const Array<int>& getHighScores(void) { return USER->highScores; }
        //  static void addHighScore(int score) { USER->highScores.push_back(score); }


    static void addGame(int score) {
        USER->masterBoard->Show_Scoreboard();
        USER->masterBoard->Add_Score(QString::fromStdString(User::getName()), QDateTime::currentDateTime(), score);
        USER->playerBoard->Add_Score(QString::fromStdString(User::getName()), QDateTime::currentDateTime(), score);
    }
    static void updateDatabase() {
        database_API dataAPI;
        dataAPI.start_connection("SQLITE", QString::fromStdString(User::getName()));
        dataAPI.update_database(USER->masterBoard);
//        dataAPI.update_database(USER->playerBoard);
        dataAPI.close_database();
    }
};

#endif  // USER_H
