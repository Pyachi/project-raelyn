#include "singleplayermenu.h"
#include <QGridLayout>
#include "mainmenu.h"
#include "src/game.h"
#include "src/entity/player.h"
#include "src/resources.h"

SingleplayerMenu* SingleplayerMenu::MENU = nullptr;

SingleplayerMenu::SingleplayerMenu()
    : QDialog(),
      characterButton("Character: Pyachi"),
      difficultyButton("Difficulty: Normal"),
      startButton("Start"),
      quitButton("Back") {
  QGridLayout* layout = new QGridLayout;
  setLayout(layout);
  setFixedSize(200, 120);

  layout->addWidget(&characterButton, 1, 1, 1, -1);
  connect(&characterButton,
          &QPushButton::clicked,
          this,
          &SingleplayerMenu::changeCharacter);

  layout->addWidget(&difficultyButton, 2, 1, 1, -1);
  connect(&difficultyButton,
          &QPushButton::clicked,
          this,
          &SingleplayerMenu::changeDifficulty);

  layout->addWidget(&startButton, 3, 1, 1, 1);
  connect(
      &startButton, &QPushButton::clicked, this, &SingleplayerMenu::startGame);

  layout->addWidget(&quitButton, 3, 2, 1, 1);
  connect(&quitButton,
          &QPushButton::clicked,
          this,
          &SingleplayerMenu::returnToMenu);
}

void SingleplayerMenu::openMenu() {
  if (MENU == nullptr)
    MENU = new SingleplayerMenu();
  MENU->show();
}

void SingleplayerMenu::changeCharacter() {

  Sound::playSound(SFX::SELECT_1, 0.1);
  if (characterButton.text().contains("Pyachi"))
    characterButton.setText("Character: Aeron");
  else
    characterButton.setText("Character: Pyachi");
}

void SingleplayerMenu::changeDifficulty() {
  Sound::playSound(SFX::SELECT_1, 0.1);
  if (difficultyButton.text().contains("Normal"))
    difficultyButton.setText("Difficulty: Hard");
  else
    difficultyButton.setText("Difficulty: Normal");
}

void SingleplayerMenu::startGame() {
  Game* game = new Game();
  game->show();
  close();
}

void SingleplayerMenu::returnToMenu() {
  Sound::playSound(SFX::SELECT_2, 0.1);
  MainMenu::openMenu();
  close();
}
